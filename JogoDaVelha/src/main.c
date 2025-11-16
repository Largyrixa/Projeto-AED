#include <stdio.h>

#include "input.h"
#include "logic.h"
#include "render.h"
#include "raylib.h"
#include "ai.h"
#include <stdbool.h>

int main()
{
  // Inicialização da janela do jogo.
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jogo da Velha");

  Texture2D textureX = LoadTexture("assets/x.png");
  Texture2D textureO = LoadTexture("assets/o.png");

  SetTargetFPS(60);

  Board myBoard;
  InitBoard(&myBoard);
  char current_player = 'X';

  // Loop principal do jogo.
  while (!WindowShouldClose())
  {
    Vector2 ClickBoardPos;
    if (GetClickBoardPos(&ClickBoardPos))
    {
      printf("Clique: (%d, %d)\n", (int)ClickBoardPos.x, (int)ClickBoardPos.y);

      bool valid_move = MakeMove(&myBoard, (int)ClickBoardPos.x, (int)ClickBoardPos.y, current_player);

      if (valid_move)
      {
        if  (current_player == 'X') current_player = 'O';
        else current_player =  'X';
      }
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
