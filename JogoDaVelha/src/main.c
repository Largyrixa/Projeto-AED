
#include "input.h"
#include "logic.h"
#include "render.h"
#include "raylib.h"
#include "ai.h" 

int main() {

    // Inicialização da janela do jogo.
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jogo da Velha");
    SetTargetFPS(60);

    // Loop principal do jogo.
    while(!WindowShouldClose()){

        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawGameGrid();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}