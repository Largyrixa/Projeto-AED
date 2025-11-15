#ifndef _LOGIC_H
#define _LOGIC_H

#include <stdbool.h>

//---Board-----------------------------------------

typedef struct Board
{
  char info[9];
} Board;

void InitBoard(Board *b);
char CheckWin(Board b);
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