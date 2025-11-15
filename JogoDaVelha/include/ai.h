#ifndef _AI_H
#define _AI_H

#ifndef MAX_SONS
  #define MAX_SONS 9
#endif

#include "logic.h"

typedef struct Node
{
  char BoardState;
  struct Node *Sons[MAX_SONS];
} GameTree;

void InitTree(GameTree *root);
void AddNode(GameTree *root, char BoardState, int index);
int GetMove(Board b, Dificulty d);
void FreeTree(GameTree *root);

#endif