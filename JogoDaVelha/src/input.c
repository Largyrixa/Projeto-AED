#include "input.h"
#include "render.h"
#include "raylib.h"

bool GetClickBoardPos(Vector2 *BoardPos)
{
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
  {
    Vector2 MPos = GetMousePosition();
    BoardPos->x = MPos.x / CELL_SIZE;
    BoardPos->y = MPos.y / CELL_SIZE;
    return true;
  }
  else
  {
    return false;
  }
}