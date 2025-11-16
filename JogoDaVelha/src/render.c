#include "render.h"
#include "raylib.h"


void DrawGameGrid()
{
  // DrawLine(startX, startY, endX, endY, color);

  // Linhas verticais
  DrawLine(CELL_SIZE, 0, CELL_SIZE, SCREEN_HEIGHT, DARKGRAY);
  DrawLine(2 * CELL_SIZE, 0, 2 * CELL_SIZE, SCREEN_HEIGHT, DARKGRAY);

  // Linhas horizontais
  DrawLine(0, CELL_SIZE, SCREEN_WIDTH, CELL_SIZE, DARKGRAY);
  DrawLine(0, 2 * CELL_SIZE, SCREEN_WIDTH, 2 * CELL_SIZE, DARKGRAY);
}
