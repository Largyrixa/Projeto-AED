#include "ai.h"
#include <stddef.h>
#include <stdlib.h>

struct Node
{
  char BoardState;
  struct Node *Sons[MAX_SONS];
}

InitTree(GameTree *root)
{
  root = NULL;
}
