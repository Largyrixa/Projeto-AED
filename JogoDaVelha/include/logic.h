#ifndef _LOGIC_H
#define _LOGIC_H

#include <stdbool.h>

//---Board-----------------------------------------

typedef struct Board Board;

void InitBoard(Board *b);
char BoardState(Board b);
bool IsValidMove (Board b, int x, int y);
bool MakeMove(Board b, int x, int y);
char GetBoardCell(Board b, int x, int y);

//-------------------------------------------------

//---Dificulty-------------------------------------

typedef enum
{
  Easy,
  Medium,
  Hard,
} Dificulty;

//-------------------------------------------------

#endif