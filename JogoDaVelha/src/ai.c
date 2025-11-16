#include "ai.h"
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