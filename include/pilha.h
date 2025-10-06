// pilha.h

#ifndef PILHA_H
#define PILHA_H

#define TAMANHO_MAX 10

#include "cores.h"

struct pilha
{
  Cor info[TAMANHO_MAX];
  unsigned char size;
};

inline void cria(pilha &p)
{
  p.size = 0;
}

inline bool cheia(const pilha &p)
{
  return p.size == TAMANHO_MAX;
}

inline bool vazia(const pilha &p)
{
  return p.size == 0;
}

/* Adiciona um elemento ao topo da pilha
 * Retorna se a operação funcionou
 */
inline bool empilha(pilha &p, Cor c)
{
  if (cheia(p))
  {
    return false;
  }

  p.info[p.size] = c;
  p.size++;
  return true;
}

/* Remove o elemento do topo da pilha
 * Retorna se a operação funcionou
 */
inline bool desempilha(pilha &p, Cor &c)
{
  if (vazia(p))
  {
    return false;
  }

  c = p.info[p.size - 1];
  p.size--;
  return true;
}

#endif // PILHA_H