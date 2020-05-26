#include "btree.h"
#include "pilaxbtree.h"
#include <stdlib.h>

PilaXBTree pb_cast(void* dato) {
  return (PilaXBTree)dato;
}

PilaXBTree pb_crear(BTNodo* nodo, int esDestruible) {
  PilaXBTree pb = malloc(sizeof(PilaXBTree));
  pb->nodo = nodo;
  pb->esDestruible = esDestruible;
  return pb;
}

void pb_destruir(PilaXBTree pb) {
  free(pb);
}
