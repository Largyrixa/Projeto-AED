// main.cpp

#include "raylib.h"
#include <iostream>
#include <string.h>

#include "cores.h"
#include "pilha.h"

// #define ASSETS_PATH -> definido pelo CMake

int main()
{
  pilha a, b;

  cria(a);
  cria(b);

  const int screen_width  = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "Corote Sort");
  SetTargetFPS(60);


  while (!WindowShouldClose())
  {
    BeginDrawing();
      ClearBackground(RAYWHITE);
      char *msg = "HELLO, WORLD";
      int fontsize = 20;
      DrawText(msg, screen_width / 2 - strlen(msg)*fontsize/4, screen_height / 2, fontsize, BLACK);
    EndDrawing();
  }

  return 0;
}