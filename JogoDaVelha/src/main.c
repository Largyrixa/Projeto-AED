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

int main()
{
  srand(time(NULL));
  // Inicialização da janela do jogo.
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jogo da Velha");

  Texture2D textureX = LoadTexture(texXPath);
  Texture2D textureO = LoadTexture(texOPath);

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
          current_player = (current_player == 'X') ? 'O' : 'X';
          CurrentBoardState = BoardState(myBoard);
        }
      }
    }
    else if (current_player == 'O' && CurrentBoardState == 'N')
    {
      int move = GetMove(myBoard, 'O', d);
      MakeMove(&myBoard, move % 3, move / 3, 'O');
      current_player = (current_player == 'X') ? 'O' : 'X';
      CurrentBoardState = BoardState(myBoard);
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawGameGrid();
    DrawBoard(myBoard, textureX, textureO);

    EndDrawing();
  }

  UnloadTexture(textureX);
  UnloadTexture(textureO);

  CloseWindow();

  return 0;
}
