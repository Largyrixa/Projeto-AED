#include <stdio.h>

#include "input.h"
#include "logic.h"
#include "render.h"
#include "raylib.h"
#include "ai.h"

#include <stdbool.h>

#ifndef ASSETS_PATH // definição do próprio CMake
#define ASSETS_PATH "assets/"
#endif

const char texXPath[] = ASSETS_PATH "x.png";
const char texOPath[] = ASSETS_PATH "o.png";

const char texVictoryXPath[] = ASSETS_PATH "vit_shewdow.png";
const char texVictoryOPath[] = ASSETS_PATH "vit_dava.png";
const char TexDrawPath[] = ASSETS_PATH "empate.png";

const char soundXPath[] = ASSETS_PATH "bazinga.wav";
const char soundOPath[] = ASSETS_PATH "ondascerebrais.wav";

Texture2D textureX;
Texture2D textureO;

// Texturas de vitórias e empate
Texture2D textureVictoryX;
Texture2D textureVictoryO;
Texture2D textureDraw;

Sound soundX;
Sound soundO;

State GameState = MENU;

// void Menu();
void GameOver(Board *, char *, char *);

int main()
{
  // Inicialização da janela do jogo.
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jogo da Velha");
  InitAudioDevice();

  textureX = LoadTexture(texXPath);
  textureO = LoadTexture(texOPath);

  textureVictoryX = LoadTexture(texVictoryXPath);
  textureVictoryO = LoadTexture(texVictoryOPath);
  textureDraw = LoadTexture(TexDrawPath);

  soundX = LoadSound(soundXPath);
  soundO = LoadSound(soundOPath);

  SetTargetFPS(60);

  Board myBoard;
  InitBoard(&myBoard);
  char current_player = 'X';
  Dificulty d = Easy;

  char CurrentBoardState = 'N';
  // Loop principal do jogo.
  while (!WindowShouldClose())
  {
    // Bloco do jogo normal
    if (CurrentBoardState == 'N')
    {
      Vector2 ClickBoardPos;
      if (current_player == 'X' && CurrentBoardState == 'N')
      {
        if (GetClickBoardPos(&ClickBoardPos))
        {
          printf("Clique: (%d, %d)\n", (int)ClickBoardPos.x, (int)ClickBoardPos.y);

          bool valid_move = MakeMove(&myBoard, (int)ClickBoardPos.x, (int)ClickBoardPos.y, current_player);

          if (valid_move)
          {
            PlaySound(soundX);
            current_player = 'O';
            CurrentBoardState = BoardState(myBoard);
          }
        }
      }
      else if (current_player == 'O' && CurrentBoardState == 'N')
      {
        WaitTime(0.6);
        int move = GetMove(myBoard, 'O', d);
        MakeMove(&myBoard, move % 3, move / 3, 'O');
        PlaySound(soundO);
        current_player = (current_player == 'X') ? 'O' : 'X';
        CurrentBoardState = BoardState(myBoard);
      }
    }

    
    BeginDrawing();
    
    ClearBackground(RAYWHITE);
    DrawBoard(myBoard, textureX, textureO);
    DrawGameGrid();

    // Bloco de Game Over
    if (CurrentBoardState != 'N')
    {
      GameOver(&myBoard, &current_player, &CurrentBoardState);
    }

    EndDrawing();
  }

  UnloadTexture(textureX);
  UnloadTexture(textureO);

  UnloadTexture(textureVictoryX);
  UnloadTexture(textureVictoryO);
  UnloadTexture(textureDraw);

  UnloadSound(soundX);
  UnloadSound(soundO);

  CloseAudioDevice();
  CloseWindow();

  return 0;
}

void GameOver(Board *b, char *current_player, char *CurrentBoardStatePtr)
{
  char CurrentBoardState = *CurrentBoardStatePtr;
  // Filtro, escurece a tela
  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 180});

  // Mensagens de vitória ou empate
  Texture2D winnerTexture = (Texture2D){0};
  const char *message = NULL;
  if (CurrentBoardState == 'X')
  {
    winnerTexture = textureVictoryX;
    message = "Shewdow Ganhou!";
  }
  else if (CurrentBoardState == 'O')
  {
    winnerTexture = textureVictoryO;
    message = "DAVi.a Ganhou!";
  }
  else if (CurrentBoardState == 'E')
  {
    winnerTexture = textureDraw;
    message = "Empate!";
  }

  if (winnerTexture.id > 0) // Só desenha se não for empate
  {
    // Lógica para centralizar e escalar a imagem
    float scale = ((double)CELL_SIZE * 1.5f) / (double)winnerTexture.width;
    float imageWidth = winnerTexture.width * scale;
    float imageHeight = winnerTexture.height * scale;

    // Posição central na tela
    Vector2 position;
    position.x = (SCREEN_WIDTH - imageWidth) / 2.0f;
    // Posiciona a imagem para que sua base fique um pouco acima do centro
    position.y = (SCREEN_HEIGHT / 2.0f) - imageHeight;

    DrawTextureEx(winnerTexture, position, 0.0f, scale, WHITE);
  }

  // Desenha o texto de vitória/empate
  int fontSize = 60;
  int textWidth = MeasureText(message, fontSize);
  DrawText(message, (SCREEN_WIDTH - textWidth) / 2, SCREEN_HEIGHT / 2 + 20, fontSize, GOLD);

  // Desenha a instrução de reinício
  const char *restartMessage = "Pressione ENTER para reiniciar";
  int restartFontSize = 30;
  int restartTextWidth = MeasureText(restartMessage, restartFontSize);
  DrawText(restartMessage, (SCREEN_WIDTH - restartTextWidth) / 2, SCREEN_HEIGHT / 2 + 90, restartFontSize, WHITE);

  if (GetKeyPressed() == KEY_ENTER)
  {
    InitBoard(b);
    *current_player = 'X';
    *CurrentBoardStatePtr = 'N';
    GameState = MENU;
  }
}