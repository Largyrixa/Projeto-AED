#ifndef _RENDER_H
#define _RENDER_H

#include "logic.h"
#include "raylib.h"

#define SCREEN_WIDTH  900
#define SCREEN_HEIGHT 900
#define BOARD_SIZE 600
#define BOARD_OFFSET_X ((SCREEN_WIDTH  - BOARD_SIZE) / 2)
#define BOARD_OFFSET_Y ((SCREEN_HEIGHT - BOARD_SIZE) / 2)
#define CELL_SIZE (BOARD_SIZE / 3)

void DrawGameGrid();
void DrawX(int x, int y, Texture2D tex);
void DrawO(int x, int y, Texture2D tex);
void DrawBoard(Board b, Texture2D tX, Texture2D tO);

#endif