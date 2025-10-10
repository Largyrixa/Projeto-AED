// main.cpp

#include <iostream>
#include <string.h>

#include "raylib.h"
#include "pilha.h"
#include "frasco.h"
#include "extra_func.h"

// #define ASSETS_PATH -> definido pelo CMake

// --- Definições Globais ----------------------------------------------------
const int LARGURA_TELA = 800;
const int ALTURA_TELA = 600;

const int CAPACIDADE_FRASCO = 4; // Cada frasco pode ter 4 unidades de líquido
const int NUM_FRASCOS = 4;
const int LARGURA_FRASCO = 80;
const int ALTURA_FRASCO = 200;
const int ALTURA_LIQUIDO = ALTURA_FRASCO / CAPACIDADE_FRASCO;

// ---------------------------------------------------------------------------

// --- Função Principal ------------------------------------------------------
int main()
{
  // Inicialização da janela
  InitWindow(LARGURA_TELA, ALTURA_TELA, "Corote Sort - Teste");
  SetTargetFPS(60);

  // Criação dos Frascos
  Frasco frascos[NUM_FRASCOS];
  for (int i = 0; i < NUM_FRASCOS; ++i)
  {
    cria(frascos[i].liquidos);
    frascos[i].rect.x = (LARGURA_TELA / (NUM_FRASCOS + 1)) * (i + 1) - (LARGURA_FRASCO / 2);
    frascos[i].rect.y = ALTURA_TELA / 2 - ALTURA_FRASCO / 2;
    frascos[i].rect.width = LARGURA_FRASCO;
    frascos[i].rect.height = ALTURA_FRASCO;
    frascos[i].seleciondo = false;
  }

  // Estado Inicial do Jogo (PARA O TESTE)
  empilha(frascos[0].liquidos, RED);
  empilha(frascos[0].liquidos, BLUE);
  empilha(frascos[0].liquidos, BLUE);
  empilha(frascos[0].liquidos, RED);
  
  empilha(frascos[1].liquidos, BLUE);
  empilha(frascos[1].liquidos, RED);
  empilha(frascos[1].liquidos, RED);
  empilha(frascos[1].liquidos, BLUE);
  // Frasco 2 começa vazio

  int frasco_origem = -1; // Índice do frasco selecionado para mover (-1 = nenhum)

  // Loop Principal do Jogo
  while (!WindowShouldClose())
  {
    // --- LÓGICA DE INPUT E JOGO ---
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      Vector2 mousePos = GetMousePosition();

      for (int i = 0; i < NUM_FRASCOS; ++i) 
      {
        if (CheckCollisionPointRec(mousePos, frascos[i].rect))
        {
          if (frasco_origem == -1)
          {
            if (!vazia(frascos[i].liquidos))
            {
              frasco_origem = i;
              frascos[i].seleciondo = true;
            }
          } else 
          {
            int frasco_destino = i;
            // Lógica de transferência
            if (frasco_origem != frasco_destino && !cheia(frascos[frasco_destino].liquidos)) {
              transferir_iguais(frascos[frasco_origem].liquidos, frascos[frasco_destino].liquidos);
            }
            // Reseta a seleção, independente se o movimento foi válido ou não
            frascos[frasco_origem].seleciondo = false;
            frasco_origem = -1;
          }
          break; // Encontramos o frasco clicado
        }
      }
    }
    // --- LÓGICA DE DESENHO ---
    BeginDrawing();
      ClearBackground(RAYWHITE);
      // Desenha os frascos e os líquidos
      for (auto& frasco : frascos)
      {
        // Desenha os líquidos dentro do frasco
        Pilha &p = frasco.liquidos;
        for (int i = 0; i < p.size; ++i) {
          // ATENÇÃO: MUDAR PARA LÓGICA "SEM ABRIR A TELEVISÃO"
          
          
          DrawRectangle(
            frasco.rect.x,
            frasco.rect.y + frasco.rect.height - (i + 1) * ALTURA_LIQUIDO,
            frasco.rect.width,
            ALTURA_LIQUIDO,
            frasco.liquidos.info[i]
          );
        }

        // Desenha a borda do frasco
        // void DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color)
        DrawRectangleLinesEx(frasco.rect, 5, frasco.seleciondo ? GREEN : BLACK);
      }
    EndDrawing();
  }

  CloseWindow();

  return 0;
}