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
  SetTargetFPS(60);

  Board* myBoard;
  InitBoard(&myBoard);
  char current_player = 'X';

  // Loop principal do jogo.
  while (!WindowShouldClose())
  {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      Vector2 posMouse = GetMousePosition();
      int x_board = (int)posMouse.x / (SCREEN_WIDTH /4);
      int y_board = (int)posMouse.y / (SCREEN_HEIGHT/4);

      bool valid_move = MakeMove(&myBoard,x_board,y_board,current_player);

      if (valid_move)
      {
        if ( current_player == 'X') current_player = 'O';
        else current_player =  'X';
      }
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawGameGrid();

    Vector2 ClickBoardPos;
    if (GetClickBoardPos(&ClickBoardPos))
    {
      printf("Clique: (%d, %d)\n", (int)ClickBoardPos.x, (int)ClickBoardPos.y);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
