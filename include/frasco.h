// frasco.h

#ifndef _FRASCO_H
#define _FRASCO_H

#include "pilha.h"
#include "raylib.h"

struct Frasco
{
  Pilha liquidos;
  Rectangle rect;
  bool seleciondo;
};


#endif // _FRASCO_H