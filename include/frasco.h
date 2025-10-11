// frasco.h

#ifndef _FRASCO_H
#define _FRASCO_H

#include "pilha.h"
#include "raylib.h"

struct Frasco
{
  Pilha liquidos;
  unsigned char capacidade;
  Rectangle rect;
  bool seleciondo;
};

void cria(Frasco &f, const unsigned char &capacidade, const Rectangle &rect)
{
  cria(f.liquidos);
  f.capacidade = capacidade;
  f.seleciondo = false;
  f.rect = rect;
}

inline bool cheio(const Frasco &f)
{
  return f.liquidos.size >= f.capacidade;
}

inline bool vazio(const Frasco &f)
{
  return f.liquidos.size == 0;
}

#endif // _FRASCO_H