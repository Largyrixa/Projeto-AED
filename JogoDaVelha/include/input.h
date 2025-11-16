#ifndef _INPUT_H
#define _INPUT_H

#include <stdbool.h>

#include "raylib.h"

typedef enum {
  MENU,
  PLAYING,
  GAME_OVER,
} State;

bool GetClickBoardPos(Vector2 *ClickBoardPos);

#endif