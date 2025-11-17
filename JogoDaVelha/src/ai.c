#include "ai.h"
#include "logic.h"
#include <stddef.h>
#include <stdlib.h>

struct Node
{
  char BoardState;
  char Player;
  struct Node *Sons[MAX_SONS];
};

GameTree *CreateTree(char BoardState, char Player)
{
  GameTree *NewTree = malloc(sizeof(GameTree));
  NewTree->BoardState = BoardState;
  NewTree->Player = Player;

  for (int i = 0; i < MAX_SONS; i++)
  {
    NewTree->Sons[i] = NULL;
  }

  return NewTree;
}

bool AddNode(GameTree *root, char BoardState, int index)
{
  if (root == NULL)
  {
    return false;
  }

  char NewPlayer;

  switch (root->Player)
  {
  case 'X':
    NewPlayer = 'O';
    break;

  case 'O':
    NewPlayer = 'X';
    break;
  }

  GameTree *NewNode = CreateTree(BoardState, NewPlayer);
  root->Sons[index] = NewNode;
}

void FreeTree(GameTree *root)
{
  if (root == NULL)
    return;

  for (int i = 0; i < MAX_SONS; i++)
  {
    FreeTree(root->Sons[i]);
  }

  free(root);
}

#define EASY_ERROR_CHANCE 60  // %
#define MEDIUM_ERROR_CHANCE 20 // %
#define HARD_ERROR_CHANCE 0    // %

#define MIN(N1, N2) ((N1 < N2) ? N1 : N2)
#define MAX(N1, N2) ((N1 > N2) ? N1 : N2)

GameTree *FindGameTree(Board b, char Player);
int MinMax(GameTree *root, char Player);

int FindRandomMove(Board b)
{
  int valid[9];
  int len = 0;
  for (int i = 0; i < 9; i++)
  {
    if (IsValidMove(b, i % 3, i / 3))
    {
      valid[len] = i;
      len++;
    }
  }

  if (len == 0)
    return -1;

  return valid[rand() % len];
}

int GetMove(Board b, char CurrPlayer, Dificulty d)
{
  GameTree *root = FindGameTree(b, CurrPlayer);

  if (root->BoardState != 'N')
  {
    return -1;
  }

  int move;
  int BestScore = -2;
  int BestMove = -1;

  for (int i = 0; i < 9; i++)
  {
    if (root->Sons[i] != NULL)
    {
      int score = MinMax(root->Sons[i], CurrPlayer);
      if (score > BestScore)
      {
        BestScore = score;
        BestMove = i;
      }
    }
  }

  FreeTree(root);

  int chance = rand() % 100;
  switch (d)
  {
  case Easy:
    if (chance <= EASY_ERROR_CHANCE)
      BestMove = FindRandomMove(b);
    break;

  case Medium:
    if (chance <= MEDIUM_ERROR_CHANCE)
      BestMove = FindRandomMove(b);
    break;

  case Hard:
    if (chance <= HARD_ERROR_CHANCE)
      BestMove = FindRandomMove(b);
    break;
  }
  return BestMove;
}

int MinMax(GameTree *root, char Player)
{
  if (root->BoardState == 'E')
  {
    return 0;
  }
  else if (root->BoardState == Player)
  {
    return 1;
  }
  else if (root->BoardState == ((Player == 'X') ? 'O' : 'X'))
  {
    return -1;
  }

  int BestScore;
  if (root->Player == Player)
  {
    BestScore = -2;

    for (int i = 0; i < 9; i++)
    {
      if (root->Sons[i] != NULL)
      {
        int score = MinMax(root->Sons[i], Player);
        BestScore = MAX(score, BestScore);
      }
    }
  }
  else
  {
    BestScore = 2;

    for (int i = 0; i < 9; i++)
    {
      if (root->Sons[i] != NULL)
      {
        int score = MinMax(root->Sons[i], Player);
        BestScore = MIN(score, BestScore);
      }
    }
  }

  return BestScore;
}

GameTree *FindGameTree(Board b, char Player)
{
  GameTree *current = CreateTree(BoardState(b), Player);

  if (current->BoardState == 'N')
  {
    for (int i = 0; i < 9; i++)
    {
      if (IsValidMove(b, i % 3, i / 3))
      {
        Board b_copy = b;
        MakeMove(&b_copy, i % 3, i / 3, Player);

        char NextPlayer = (Player == 'O') ? 'X' : 'O';

        current->Sons[i] = FindGameTree(b_copy, NextPlayer);
      }
    }
  }

  return current;
}