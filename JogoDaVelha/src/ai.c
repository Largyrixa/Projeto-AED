#include "ai.h"
#include <stddef.h>
#include <stdlib.h>

struct Node
{
  char BoardState;
  char Player;
  struct Node *Sons[MAX_SONS];
};

void InitTree(GameTree *root)
{
  root = NULL;
}

