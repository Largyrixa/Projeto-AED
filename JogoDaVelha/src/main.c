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
const char soundWinXPath[] = ASSETS_PATH "Shadow_4EVER.wav";

const char soundOPath[] = ASSETS_PATH "ondascerebrais.wav";
const char soundWinOPath[] = ASSETS_PATH "contemplemomago.wav";

const char soundDrawPath[] = ASSETS_PATH "empatebrutal.wav";

int main()
{
  // Inicialização da janela do jogo.
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jogo da Velha");
  InitAudioDevice();
  
  Texture2D textureX = LoadTexture(texXPath);
  Texture2D textureO = LoadTexture(texOPath);

  //Texturas de vitórias e empate
  Texture2D textureVictoryX = LoadTexture(texVictoryXPath);
  Texture2D textureVictoryO = LoadTexture(texVictoryOPath);
  Texture2D textureDraw = LoadTexture(TexDrawPath);

  Sound soundX = LoadSound(soundXPath);
  Sound soundWinX = LoadSound(soundWinXPath);

  Sound soundO = LoadSound(soundOPath);
  Sound soundWinO = LoadSound(soundWinOPath);

  Sound soundDraw = LoadSound(soundDrawPath);

  SetTargetFPS(60);

  restart:
  Board myBoard;
  InitBoard(&myBoard);
  char current_player = 'X';
  Dificulty d = Easy;

  char CurrentBoardState = 'N';
  // Loop principal do jogo.
  while (!WindowShouldClose())
  {
    if (CurrentBoardState == 'N') {
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
        WaitTime(0.5);
        int move = GetMove(myBoard, 'O', d);
        MakeMove(&myBoard, move % 3, move / 3, 'O');
        PlaySound(soundO);
        current_player = (current_player == 'X') ? 'O' : 'X';
        CurrentBoardState = BoardState(myBoard);
      }
    }
    if (CurrentBoardState != 'N')
    {
      if (GetKeyPressed() == KEY_ENTER)
      {
        StopSound(soundWinX);
        StopSound(soundWinO);
        StopSound(soundDraw);
        goto restart;
      }
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawBoard(myBoard, textureX, textureO);
    DrawGameGrid();

    //Bloco de GAME OVER
    if (CurrentBoardState != 'N')
    {
      // Filtro, escurece a tela
      DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){ 0, 0, 0, 180 });

      // Mensagens de vitória ou empate
      Texture2D winnerTexture = (Texture2D){0};
      const char *message = NULL;
      if (CurrentBoardState == 'X')
      {
        winnerTexture = textureVictoryX;
        message = "Shewdow Ganhou!";

        // Toca o som de vitória do jogador X
        // !! SEPARADO PARA NÃO CONFLITAR COM A IMAGEM !!
        if (!IsSoundPlaying(soundWinX))
        {
          PlaySound(soundWinX);
        }
      }
      else if (CurrentBoardState == 'O')
      {
        winnerTexture = textureVictoryO;
        message = "DAVi.a Ganhou!";

        if (!IsSoundPlaying(soundWinO))
        {
          PlaySound(soundWinO);
        }
      }
      else if (CurrentBoardState == 'E')
      {
        winnerTexture = textureDraw;
        message = "Empate!";

        if (!IsSoundPlaying(soundDraw))
        {
          PlaySound(soundDraw);
        }
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
    }

    EndDrawing();
  }

  UnloadTexture(textureX);
  UnloadTexture(textureO);

  UnloadTexture(textureVictoryX);
  UnloadTexture(textureVictoryO);
  UnloadTexture(textureDraw);

  UnloadSound(soundX);
  UnloadSound(soundWinX);
  UnloadSound(soundO);
  UnloadSound(soundWinO);
  UnloadSound(soundDraw);

  CloseAudioDevice();
  CloseWindow();

  return 0;
}
