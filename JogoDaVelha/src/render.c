#include "render.h"
#include "raylib.h"

const int cell_size = SCREEN_WIDTH / 3;

void DrawGameGrid(){

    // DrawLine(startX, startY, endX, endY, color);

    // Linhas verticais
    DrawLine(    cell_size, 0 ,     cell_size, SCREEN_HEIGHT, DARKGRAY);
    DrawLine(2 * cell_size, 0 , 2 * cell_size, SCREEN_HEIGHT, DARKGRAY);

    // Linhas horizontais
    DrawLine(0 ,     cell_size, SCREEN_WIDTH,     cell_size , DARKGRAY);
    DrawLine(0 , 2 * cell_size, SCREEN_WIDTH, 2 * cell_size , DARKGRAY);
}
