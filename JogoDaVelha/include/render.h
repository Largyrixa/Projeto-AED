#ifndef _RENDER_H
#define _RENDER_H

#include "logic.h"

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600
<<<<<<< HEAD
#define CELL_SIZE (SCREEN_HEIGHT / 3)
=======
#define cell_size (SCREEN_WIDTH / 3)
>>>>>>> d39c75b (Desenho dos jogadores e mais um pouco do loop principal)

void DrawGameGrid();
void DrawX(int x, int y);
void DrawO(int x, int y);
void DrawBoard(Board b);

#endif