#include <stdio.h>
#include <stdbool.h>

#include "raylib.h"
#include "input.h"
#include "logic.h"
#include "render.h"
#include "ai.h"

// --- Definições de Caminhos (Assets) ---
#ifndef ASSETS_PATH
  #define ASSETS_PATH "assets/"
#endif

// --- Estruturas Auxiliares ---

// Agrupa todos os recursos carregados para evitar variáveis soltas na main
typedef struct
{
  Texture2D texX;
  Texture2D texO;
  Texture2D texVictoryX;
  Texture2D texVictoryO;
  Texture2D texDraw;
  Sound soundX;
  Sound soundO;
  Sound soundWinX;
  Sound soundWinO;
  Sound soundDraw;
} GameResources;

// Agrupa o estado mutável do jogo
typedef struct
{
  Board board;
  char currentPlayer; // 'X' ou 'O'
  char boardState;    // 'N' (Normal), 'X', 'O', 'E' (Empate)
  Difficulty aiDifficulty;
  State currentState;
  float timeSinceLastMove; // Para controlar o delay da IA
} GameSession;

// --- Protótipos das Funções Locais ---
GameResources LoadGameResources();
void UnloadGameResources(GameResources *res);
void ResetGame(GameSession *session);
void UpdateGame(GameSession *session, GameResources *res);
void DrawGame(GameSession *session, GameResources *res);
void DrawMenu(GameSession *session);

// --- Função Principal ---
int main()
{
  // 1. Inicialização do Sistema
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jogo da Velha");
  InitAudioDevice();
  SetTargetFPS(60);

  // 2. Carregamento de Recursos
  GameResources res = LoadGameResources();

  // 3. Inicialização da Sessão de Jogo
  GameSession session;
  session.currentState = MENU; // Começa no Menu
  session.aiDifficulty = Easy; // Dificuldade padrão
  ResetGame(&session);

  // 4. Game Loop Principal
  while (!WindowShouldClose())
  {
    UpdateGame(&session, &res);
    DrawGame(&session, &res);
  }

  // 5. Limpeza
  UnloadGameResources(&res);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}

// --- Implementação das Funções ---

void UpdateGame(GameSession *s, GameResources *res)
{
  switch (s->currentState)
  {
  case MENU:
  {
    // Seleção de Dificuldade
    if (IsKeyPressed(KEY_RIGHT))
    {
      s->aiDifficulty = (s->aiDifficulty + 1) % 3;
    }
    if (IsKeyPressed(KEY_LEFT))
    {
      s->aiDifficulty = (s->aiDifficulty == 0) ? (Hard) : (s->aiDifficulty - 1);
      if (s->aiDifficulty < 0)
        s->aiDifficulty = Hard;
    }

    // Iniciar Jogo
    if (IsKeyPressed(KEY_ENTER))
    {
      ResetGame(s); // Garante tabuleiro limpo
      s->currentState = PLAYING;
    }
  }
  break;

  case PLAYING:
  {
    // Se o jogo acabou, espera input para ir para Game Over ou Menu
    if (s->boardState != 'N')
    {
      s->currentState = GAME_OVER;
      return;
    }

    // Turno do Jogador (X)
    if (s->currentPlayer == 'X')
    {
      int clickPos[2];
      if (GetClickBoardPos(&clickPos[0], &clickPos[1])) // Função do input.c
      {
        if (MakeMove(&s->board, clickPos[0], clickPos[1], 'X'))
        {
          PlaySound(res->soundX);
          s->currentPlayer = 'O';
          s->boardState = BoardState(s->board);
          s->timeSinceLastMove = 0; // Reseta timer para delay da IA
        }
      }
    }
    // Turno da IA (O)
    else if (s->currentPlayer == 'O')
    {
      s->timeSinceLastMove += GetFrameTime();

      // Pequeno delay para parecer que a IA está "pensando" (0.5s)
      if (s->timeSinceLastMove >= 0.5f)
      {
        int move = GetMove(s->board, 'O', s->aiDifficulty);

        // Verifica se GetMove retornou erro (-1) ou movimento válido
        if (move != -1)
        {
          MakeMove(&s->board, move % 3, move / 3, 'O');
          PlaySound(res->soundO);
          s->currentPlayer = 'X';
          s->boardState = BoardState(s->board);
        }
      }
    }
  }
  break;

  case GAME_OVER:
  {
    // Toca os sons de vitória apenas uma vez (verificação feita no Draw ou aqui)
    // Aqui estamos apenas gerenciando a transição de volta ao menu ou reinício

    if (IsKeyPressed(KEY_ENTER))
    {
      // Para sons antes de reiniciar
      StopSound(res->soundWinX);
      StopSound(res->soundWinO);
      StopSound(res->soundDraw);

      // Volta para o Menu (ou poderia ser ResetGame para jogar direto)
      s->currentState = MENU;
    }
  }
  break;
  }
}

void DrawGame(GameSession *s, GameResources *res)
{
  BeginDrawing();
  ClearBackground(RAYWHITE);

  switch (s->currentState)
  {
  case MENU:
    DrawMenu(s);
    break;

  case PLAYING:
  case GAME_OVER:
  {
    // Desenha o jogo base
    DrawBoard(s->board, res->texX, res->texO);
    DrawGameGrid();

    // Se estiver em GAME OVER, desenha o overlay
    if (s->currentState == GAME_OVER)
    {
      DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 180});

      Texture2D winnerTex = {0};
      const char *msg = "";
      Color msgColor = WHITE;

      if (s->boardState == 'X')
      {
        winnerTex = res->texVictoryX;
        msg = "Shewdow Venceu!";
        msgColor = RED;
        if (!IsSoundPlaying(res->soundWinX))
          PlaySound(res->soundWinX);
      }
      else if (s->boardState == 'O')
      {
        winnerTex = res->texVictoryO;
        msg = "DAVi.a Venceu!";
        msgColor = BLUE;
        if (!IsSoundPlaying(res->soundWinO))
          PlaySound(res->soundWinO);
      }
      else
      {
        winnerTex = res->texDraw;
        msg = "EMPATE BRUTAL!";
        msgColor = GOLD;
        if (!IsSoundPlaying(res->soundDraw))
          PlaySound(res->soundDraw);
      }

      // Desenha Imagem da Vitória/Empate
      if (winnerTex.id > 0)
      {
        float scale = ((double)CELL_SIZE * 1.5f) / (double)winnerTex.width;
        Vector2 pos = {
            (SCREEN_WIDTH - winnerTex.width * scale) / 2.0f,
            (SCREEN_HEIGHT / 2.0f) - (winnerTex.height * scale)};
        DrawTextureEx(winnerTex, pos, 0.0f, scale, WHITE);
      }

      // Textos
      DrawText(msg, (SCREEN_WIDTH - MeasureText(msg, 60)) / 2, SCREEN_HEIGHT / 2 + 20, 60, msgColor);

      const char *sub = "Pressione ENTER para o Menu";
      DrawText(sub, (SCREEN_WIDTH - MeasureText(sub, 30)) / 2, SCREEN_HEIGHT / 2 + 90, 30, LIGHTGRAY);
    }
  }
  break;
  }

  EndDrawing();
}

void DrawMenu(GameSession *s)
{
  // Fundo simples ou estilizado
  ClearBackground(RAYWHITE);

  const char *title = "JOGO DA VELHA";
  DrawText(title, (SCREEN_WIDTH - MeasureText(title, 80)) / 2, 150, 80, DARKGRAY);

  const char *subtitle = "Escolha a Dificuldade:";
  DrawText(subtitle, (SCREEN_WIDTH - MeasureText(subtitle, 40)) / 2, 350, 40, GRAY);

  // Mostra a dificuldade atual
  const char *diffText;
  Color diffColor;
  switch (s->aiDifficulty)
  {
  case Easy:
    diffText = "< FACIL >";
    diffColor = GREEN;
    break;
  case Medium:
    diffText = "< MEDIO >";
    diffColor = ORANGE;
    break;
  case Hard:
    diffText = "< DIFICIL >";
    diffColor = RED;
    break;
  }

  DrawText(diffText, (SCREEN_WIDTH - MeasureText(diffText, 50)) / 2, 420, 50, diffColor);

  const char *instr = "Use as Setas ESQUERDA/DIREITA para mudar";
  DrawText(instr, (SCREEN_WIDTH - MeasureText(instr, 20)) / 2, 500, 20, LIGHTGRAY);

  const char *start = "Pressione ENTER para Iniciar";
  DrawText(start, (SCREEN_WIDTH - MeasureText(start, 30)) / 2, 700, 30, BLACK);
}

void ResetGame(GameSession *s)
{
  InitBoard(&s->board);
  s->currentPlayer = 'X';
  s->boardState = 'N';
  s->timeSinceLastMove = 0;
}

GameResources LoadGameResources()
{
  GameResources res;
  res.texX = LoadTexture(ASSETS_PATH "x.png");
  res.texO = LoadTexture(ASSETS_PATH "o.png");
  res.texVictoryX = LoadTexture(ASSETS_PATH "vit_shewdow.png");
  res.texVictoryO = LoadTexture(ASSETS_PATH "vit_dava.png");
  res.texDraw = LoadTexture(ASSETS_PATH "empate.png");

  res.soundX = LoadSound(ASSETS_PATH "bazinga.wav");
  res.soundO = LoadSound(ASSETS_PATH "ondascerebrais.wav");
  res.soundWinX = LoadSound(ASSETS_PATH "Shadow_4EVER.wav");
  res.soundWinO = LoadSound(ASSETS_PATH "contemplemomago.wav");
  res.soundDraw = LoadSound(ASSETS_PATH "empatebrutal.wav");

  return res;
}

void UnloadGameResources(GameResources *res)
{
  UnloadTexture(res->texX);
  UnloadTexture(res->texO);
  UnloadTexture(res->texVictoryX);
  UnloadTexture(res->texVictoryO);
  UnloadTexture(res->texDraw);

  UnloadSound(res->soundX);
  UnloadSound(res->soundO);
  UnloadSound(res->soundWinX);
  UnloadSound(res->soundWinO);
  UnloadSound(res->soundDraw);
}