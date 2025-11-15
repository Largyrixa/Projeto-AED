#ifndef _LOGIC_H
#define _LOGIC_H

#include <stdbool.h>

//---Board-----------------------------------------

typedef struct Board Board;

void InitBoard(Board *b);
char CheckWin(Board b);
char CheckDraw(Board b);
bool MakeMove(Board b, int x, int y);
char GetBoardCell(Board b, int x, int y);

//-------------------------------------------------

//---Dificulty-------------------------------------

typedef enum {
  Easy,
  Medium,
  Hard,
} Dificulty;

//-------------------------------------------------

#endif