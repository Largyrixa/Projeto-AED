#ifndef _RENDER_H
#define _RENDER_H

#include "logic.h"
#include "raylib.h"

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600
#define CELL_SIZE (SCREEN_HEIGHT / 3)

void DrawGameGrid();
void DrawX(int x, int y, Texture2D tex);
void DrawO(int x, int y, Texture2D tex);
void DrawBoard(Board b, Texture2D tX, Texture2D tO);

#endif