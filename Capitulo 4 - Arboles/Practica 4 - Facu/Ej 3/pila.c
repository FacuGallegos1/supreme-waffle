#include "pila.h"
#include <stdlib.h>

Pila pila_crear() {
  Pila pila = malloc(sizeof(Pila));
  pila->ultimo = NULL;
  return pila;
}

int pila_is_empty(Pila pila) {
  return pila->ultimo == NULL;
}

Pila pila_push(Pila pila, void* dato) {
  GPNodo* nuevoNodo = malloc(sizeof(GPNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->ant = pila->ultimo;
  pila->ultimo = nuevoNodo;
  return pila;
}

void* pila_top(Pila pila) {
  if (pila_is_empty(pila)) {
    return NULL;
  } else {
    return pila->ultimo->dato;
  }
}

void pila_pop(Pila pila) {
  if (!pila_is_empty(pila)) {
    GPNodo* temp = pila->ultimo->ant;
    free(pila->ultimo);
    pila->ultimo = temp;
  }
}

Pila pila_pop_d(Pila pila, Destruir d) {
  if (!pila_is_empty(pila)) {
    d(pila->ultimo->dato);
    GPNodo* temp = pila->ultimo->ant;
    free(pila->ultimo);
    pila->ultimo = temp;
  }
  return pila;
}

void pila_destruir(Pila pila) {
  while (!pila_is_empty(pila)) {
    pila_pop(pila);
  }
  free(pila);
}

void pila_destruir_d(Pila pila, Destruir d) {
  while (!pila_is_empty(pila)) {
    pila_pop_d(pila, d);
  }
  free(pila);
}
