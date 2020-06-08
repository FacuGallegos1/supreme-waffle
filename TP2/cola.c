#include <stdlib.h>
#include <stdio.h>
#include "cola.h"

Cola cola_crear() {
  Cola cola = malloc(sizeof(Cola));
  cola->primero = NULL;
  cola->ultimo = NULL;
  return cola;
}

int cola_es_vacia(Cola cola) {
  return (cola->primero == NULL && cola->ultimo == NULL);
}

void cola_encolar(Cola cola, void* dato) {
  GNodo* nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->ant = NULL;
  if (cola_es_vacia(cola)) {
    cola->ultimo = nuevoNodo;
    cola->primero = nuevoNodo;
  } else {
    cola->ultimo->ant = nuevoNodo;
    cola->ultimo = nuevoNodo;
  }
}

void* cola_primero(Cola cola) {
  if (cola_es_vacia(cola))
    return NULL;
  else
    return cola->primero->dato;
}

void cola_desencolar(Cola cola) {
  if (cola_es_vacia(cola)) {
    printf("La cola ya está vacía\n");
    return;
  }
  GNodo* temp = cola->primero;
  if (cola->primero == cola->ultimo) { // Cuando quede un sólo elemento
    cola->primero = NULL;
    cola->ultimo = NULL;
  } else {
    cola->primero = cola->primero->ant;
  }
  free(temp);
}

void cola_destruir(Cola cola) {
  while(!cola_es_vacia(cola)) {
    cola_desencolar(cola);
  }
  free(cola);
}
