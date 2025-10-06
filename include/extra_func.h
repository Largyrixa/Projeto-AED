// extra_func.h

#ifndef FUNC_H
#define FUNC_H

#include "pilha.h"
#include "cores.h"

/* Transfere todos os primeiros elementos iguais da pilha 'a' para a pilha 'b'
 * Retorna se a operação deu certo
 */
inline bool transferir_iguais(pilha &a, pilha &b)
{
  if (vazia(a) || cheia(b))
  {
    return false;
  }

  Cor primeira, x;
  bool okA = desempilha(a, primeira);
  bool okB = empilha(b, primeira);

  while (okA && okB)
  {
    okA = desempilha(a, x);
    if (x == primeira)
    {
      empilha(b, x);
    }
    else
    {
      break; // acabaram os iguais
    }
  }

  return true;
}


/* Verifica se todos os elementos da pilha são iguais
 */
inline bool todos_iguais(pilha &a)
{
  if (vazia(a))
  {
    return false;
  }

  pilha paux;
  cria(paux);

  Cor x, y;
  bool ok = desempilha(a, x);
  empilha(paux, x);

  while (ok)
  {
    ok = desempilha(a, y);
    empilha(paux, y);
    if (x != y)
    {
      return false;
    }
    x = y;
  }

  ok = desempilha(paux, x);
  empilha(a, x);

  while (ok)
  {
    ok = desempilha(paux, x);
    empilha(a, x);
  }

  return true;
}

#endif // FUNC_H