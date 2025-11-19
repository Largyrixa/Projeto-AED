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

// --- Constantes de Layout do Menu ---
#define BTN_PLAY_W 200
#define BTN_PLAY_H 50
#define BTN_DIFF_W 100
#define BTN_DIFF_H 50
#define BTN_SPACING 20

// --- Estruturas Auxiliares ---

// Agrupa todos os recursos carregados
typedef struct
{
  Texture2D texX;
  Texture2D texO;
  Texture2D texVictoryX;
  Texture2D texVictoryO;
  Texture2D texDraw;
  Texture2D texBackground; // Adicionado background aqui
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
  char currentPlayer;
  char boardState;
  Difficulty aiDifficulty; // Atenção: verifique se no seu enum é Difficulty ou Difficulty
  State currentState;
  float timeSinceLastMove;
} GameSession;

// --- Protótipos ---
GameResources LoadGameResources();
void UnloadGameResources(GameResources *res);
void ResetGame(GameSession *session);
void UpdateGame(GameSession *session, GameResources *res);
void DrawGame(GameSession *session, GameResources *res);
void DrawMenu(GameSession *session, GameResources *res); // Menu agora recebe resources
Rectangle GetPlayBtnRect();
Rectangle GetDiffBtnRect(int index); // index 0, 1 ou 2

// --- Função Principal ---
int main()
{
  // 1. Inicialização
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jogo da Velha");
  InitAudioDevice();
  SetTargetFPS(60);

  // 2. Carregamento
  GameResources res = LoadGameResources();

  // 3. Sessão
  GameSession session;
  session.currentState = MENU;
  session.aiDifficulty = Easy;
  ResetGame(&session);

  // 4. Loop
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

// Funções auxiliares para calcular posição dos botões (usadas no Update e no Draw)
Rectangle GetPlayBtnRect()
{
  return (Rectangle){
      (SCREEN_WIDTH - BTN_PLAY_W) / 2.0f,
      (SCREEN_HEIGHT - BTN_PLAY_H) / 2.0f,
      BTN_PLAY_W, BTN_PLAY_H};
}

Rectangle GetDiffBtnRect(int index)
{
  float totalWidth = (BTN_DIFF_W * 3) + (BTN_SPACING * 2);
  float startX = (SCREEN_WIDTH - totalWidth) / 2.0f;
  float y = (SCREEN_HEIGHT / 2.0f) + (BTN_PLAY_H / 2.0f) + BTN_SPACING;

  return (Rectangle){
      startX + index * (BTN_DIFF_W + BTN_SPACING),
      y,
      BTN_DIFF_W, BTN_DIFF_H};
}

void UpdateGame(GameSession *s, GameResources *res)
{
  switch (s->currentState)
  {
  case MENU:
  {
    Vector2 mousePoint = GetMousePosition();
    Rectangle btnPlay = GetPlayBtnRect();
    Rectangle btnEasy = GetDiffBtnRect(0);
    Rectangle btnMed = GetDiffBtnRect(1);
    Rectangle btnHard = GetDiffBtnRect(2);

    // Lógica do Botão JOGAR
    if (CheckCollisionPointRec(mousePoint, btnPlay))
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {
        ResetGame(s);
        s->currentState = PLAYING;
      }
    }

    // Lógica dos Botões de Dificuldade
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      if (CheckCollisionPointRec(mousePoint, btnEasy))
        s->aiDifficulty = Easy;
      if (CheckCollisionPointRec(mousePoint, btnMed))
        s->aiDifficulty = Medium;
      if (CheckCollisionPointRec(mousePoint, btnHard))
        s->aiDifficulty = Hard;
    }
  }
  break;

  case PLAYING:
  {
    if (s->boardState != 'N')
    {
      s->currentState = GAME_OVER;
      return;
    }

    if (s->currentPlayer == 'X')
    {
      int clickPos[2];
      // Ajustei para usar Vector2 conforme seu input.h original
      if (GetClickBoardPos(&clickPos[0], &clickPos[1]))
      {
        if (MakeMove(&s->board, clickPos[0], clickPos[1], 'X'))
        {
          PlaySound(res->soundX);
          s->currentPlayer = 'O';
          s->boardState = BoardState(s->board);
          s->timeSinceLastMove = 0;
        }
      }
    }
    else if (s->currentPlayer == 'O')
    {
      s->timeSinceLastMove += GetFrameTime();
      if (s->timeSinceLastMove >= 0.5f)
      {
        int move = GetMove(s->board, 'O', s->aiDifficulty);
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
    if (IsKeyPressed(KEY_ENTER))
    {
      StopSound(res->soundWinX);
      StopSound(res->soundWinO);
      StopSound(res->soundDraw);
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
    DrawMenu(s, res);
    break;

  case PLAYING:
  case GAME_OVER:
  {
    DrawBoard(s->board, res->texX, res->texO);
    DrawGameGrid();

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

      if (winnerTex.id > 0)
      {
        float scale = ((double)CELL_SIZE * 1.5f) / (double)winnerTex.width;
        Vector2 pos = {
            (SCREEN_WIDTH - winnerTex.width * scale) / 2.0f,
            (SCREEN_HEIGHT / 2.0f) - (winnerTex.height * scale)};
        DrawTextureEx(winnerTex, pos, 0.0f, scale, WHITE);
      }

      DrawText(msg, (SCREEN_WIDTH - MeasureText(msg, 60)) / 2, SCREEN_HEIGHT / 2 + 20, 60, msgColor);
      const char *sub = "Pressione ENTER para o Menu";
      DrawText(sub, (SCREEN_WIDTH - MeasureText(sub, 30)) / 2, SCREEN_HEIGHT / 2 + 90, 30, LIGHTGRAY);
    }
  }
  break;
  }

  EndDrawing();
}

void DrawMenu(GameSession *s, GameResources *res)
{
  // Desenha fundo
  DrawTexture(res->texBackground, 0, 0, WHITE);

  Vector2 mousePos = GetMousePosition();

  // Cores
  Color btnColor = BLACK;
  Color hoverColor = DARKGRAY;
  Color selectedColor = MAROON;

  // Botão JOGAR
  Rectangle playRect = GetPlayBtnRect();
  bool playHover = CheckCollisionPointRec(mousePos, playRect);
  DrawRectangleRec(playRect, playHover ? hoverColor : btnColor);

  const char *txtPlay = "JOGAR";
  DrawText(txtPlay,
           playRect.x + (playRect.width - MeasureText(txtPlay, 20)) / 2,
           playRect.y + (playRect.height - 20) / 2, 20, RAYWHITE);

  // Botões de Dificuldade
  const char *diffTexts[3] = {"FÁCIL", "MÉDIO", "DIFÍCIL"};
  Difficulty diffs[3] = {Easy, Medium, Hard};

  for (int i = 0; i < 3; i++)
  {
    Rectangle r = GetDiffBtnRect(i);
    bool hover = CheckCollisionPointRec(mousePos, r);

    Color c = btnColor;
    if (s->aiDifficulty == diffs[i])
      c = selectedColor; // Selecionado
    else if (hover)
      c = hoverColor; // Mouse em cima

    DrawRectangleRec(r, c);
    DrawText(diffTexts[i],
             r.x + (r.width - MeasureText(diffTexts[i], 18)) / 2,
             r.y + (r.height - 18) / 2, 18, RAYWHITE);
  }
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
  res.texBackground = LoadTexture(ASSETS_PATH "background.png");

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
  UnloadTexture(res->texBackground); // Não esqueça de descarregar

  UnloadSound(res->soundX);
  UnloadSound(res->soundO);
  UnloadSound(res->soundWinX);
  UnloadSound(res->soundWinO);
  UnloadSound(res->soundDraw);
}