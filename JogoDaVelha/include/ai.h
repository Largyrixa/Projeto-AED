#ifndef _AI_H
#define _AI_H

#ifndef MAX_SONS
  #define MAX_SONS 9
#endif

#include "logic.h"

/*
 Essa árvore funciona da seguinte forma:
 - Armazena o estado atual do tabuleiro em 'BoardState'
 - Armazena o player atual em 'Player'
 - Cada index de 'Sons' traduz para uma jogada no tabuleiro, por isso 9
*/
typedef struct Node GameTree;

GameTree *CreateTree(char BoardState, char Player);
bool AddNode(GameTree *root, char BoardState, int index);
int GetMove(Board b, Dificulty d);
void FreeTree(GameTree *root);

#endif