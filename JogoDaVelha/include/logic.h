#ifndef _LOGIC_H
#define _LOGIC_H

#include <stdbool.h>

//---Board-----------------------------------------

typedef struct Board
{
  char info[9];
} Board;

void InitBoard(Board *b);
char BoardState(Board b);
bool IsValidMove (Board b, int x, int y);
bool MakeMove(Board *b, int x, int y, char player);
char GetBoardCell(Board b, int x, int y);

//-------------------------------------------------

//---Difficulty-------------------------------------

typedef enum
{
  Easy,
  Medium,
  Hard,
} Difficulty;

//-------------------------------------------------

#endif