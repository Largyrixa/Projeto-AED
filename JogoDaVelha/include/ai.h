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

/*
  Cria uma nóva Game Tree dinamicamente alocada:
  @param BoardState: Estado do tabuleiro na árvore atual
  @param Player: Player do tabuleiro atual
*/
GameTree *CreateTree(char BoardState, char Player);

/*
  Calcula o movimento do bot conforme a dificuldade por meio de uma árvore de possibilidades 'GameTree'
  Basicamente uma versão com diferentes dificuldades do minmax
*/
int GetMove(Board b, char Bot, Dificulty d);
void FreeTree(GameTree *root);

#endif