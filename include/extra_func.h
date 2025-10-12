// extra_func.h

#ifndef FUNC_H
#define FUNC_H

#include "pilha.h"
#include "raylib.h"

inline bool cores_sao_iguais(const Color &cor1, const Color &cor2)
{
  return cor1.r == cor2.r &&
         cor1.g == cor2.g &&
         cor1.b == cor2.b &&
         cor1.a == cor2.a;
}

bool ver_topo (Pilha &p, Color &x)
{
  bool ok = desempilha(p, x);
  if (!ok)
    return false;

  empilha(p, x);
  return true;
}

/* Transfere todos os primeiros elementos iguais da Pilha 'a' para a Pilha 'b'
 * Retorna se a operação deu certo
 */
inline bool transferir_iguais(Frasco &a, Frasco &b)
{
  if (vazio(a) || cheio(b))
  {
    return false;
  }

  Color corBase, corTopo; 

  ver_topo(a.liquidos, corBase);

  while(!vazio(a) && !cheio(b))
  {
    ver_topo(a.liquidos, corTopo);

    if (cores_sao_iguais(corTopo, corBase))
    {
      Color corMovida;
      desempilha(a.liquidos, corMovida);
      empilha(b.liquidos, corMovida);
    }
    else
    {
      break;
    }
  }

  return true;
}


/* Verifica se todos os elementos da Pilha são iguais
 */
inline bool todos_iguais(Pilha &a)
{
  if (vazia(a))
  {
    return false;
  }

  Pilha paux;
  cria(paux);

  Color x, y;
  bool ok = desempilha(a, x);
  empilha(paux, x);

  while (ok)
  {
    ok = desempilha(a, y);
    empilha(paux, y);
    if (!cores_sao_iguais(x, y))
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

void desenhar_liquidos(Frasco &f, const int ALTURA_LIQUIDO)
{
  Color cor_liquido;
  int nivel_liquido = 0;

  Pilha passis;
  cria(passis);

  while(!vazia(f.liquidos))
  {
    desempilha(f.liquidos, cor_liquido);
    empilha(passis, cor_liquido);

    DrawRectangle(
      f.rect.x,
      f.rect.y + f.rect.height - (nivel_liquido + 1) * ALTURA_LIQUIDO,
      f.rect.width,
      ALTURA_LIQUIDO,
      f.liquidos.info[nivel_liquido]
    );

    nivel_liquido++;
  }

  while(!vazia(passis))
  {
    desempilha(passis, cor_liquido);
    empilha(f.liquidos, cor_liquido);
  }
}


#endif // FUNC_H