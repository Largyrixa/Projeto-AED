#include "input.h"
#include "render.h"
#include "raylib.h"

bool GetClickBoardPos(Vector2 *BoardPos)
{
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
  {
    Vector2 MPos = GetMousePosition();

    if (MPos.x < BOARD_OFFSET_X || MPos.x > (BOARD_OFFSET_X + BOARD_SIZE) ||
        MPos.y < BOARD_OFFSET_Y || MPos.y > (BOARD_OFFSET_Y + BOARD_SIZE)
       )
    {
      return false;
    }

    double relative_x = MPos.x - BOARD_OFFSET_X;
    double relative_y = MPos.y - BOARD_OFFSET_Y;

    BoardPos->x = (int)(relative_x / CELL_SIZE);
    BoardPos->y = (int)(relative_y / CELL_SIZE);
    return true;
  }
  else
  {
    return false;
  }
}