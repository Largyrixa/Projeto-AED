#include <stdio.h>

#include "input.h"
#include "logic.h"
#include "render.h"
#include "raylib.h"
#include "ai.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifndef ASSETS_PATH // definição do próprio CMake
#define ASSETS_PATH "assets/"
#endif

const char texXPath[] = ASSETS_PATH "x.png";
const char texOPath[] = ASSETS_PATH "o.png";

const char soundXPath[] = ASSETS_PATH "bazinga.wav";
const char soundOPath[] = ASSETS_PATH "ondascerebrais.wav";

int main()
{
  srand(time(NULL));
  // Inicialização da janela do jogo.
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jogo da Velha");
  InitAudioDevice();

  Texture2D textureX = LoadTexture(texXPath);
  Texture2D textureO = LoadTexture(texOPath);

  Sound soundX = LoadSound(soundXPath);
  Sound soundO = LoadSound(soundOPath);

  SetTargetFPS(60);

  Board myBoard;
  InitBoard(&myBoard);
  char current_player = 'X';
  Dificulty d = Easy;

  char CurrentBoardState = 'N';
  // Loop principal do jogo.
  while (!WindowShouldClose())
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
      WaitTime(0.5);
      int move = GetMove(myBoard, 'O', d);
      MakeMove(&myBoard, move % 3, move / 3, 'O');
      PlaySound(soundO);
      current_player = (current_player == 'X') ? 'O' : 'X';
      CurrentBoardState = BoardState(myBoard);
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawBoard(myBoard, textureX, textureO);
    DrawGameGrid();

    EndDrawing();
  }

  UnloadTexture(textureX);
  UnloadTexture(textureO);

  UnloadSound(soundX);
  UnloadSound(soundO);

  CloseAudioDevice();
  CloseWindow();

  return 0;
}
