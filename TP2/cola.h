#ifndef __COLA_H__
#define __COLA_H__

typedef struct _GNodo{
  void* dato;
  struct _GNodo* ant;
} GNodo;

typedef struct {
  GNodo* primero;
  GNodo* ultimo;
}_Cola;

typedef _Cola* Cola;

/**
 * Crea la cola.
 */
Cola cola_crear();

/**
 * Determina si la cola es vacía.
 */
int cola_es_vacia(Cola cola);

/**
 * Encola un elemento.
 */
void cola_encolar(Cola cola, void* dato);

/**
 * Devuelve el primer elemento (sin desencolarlo).
 */
void* cola_primero(Cola cola);

/**
 * Desencola el primer elemento.
 */
void cola_desencolar(Cola cola);

/**
 * Destruye la cola.
 */
void cola_destruir(Cola cola);

#endif /* __COLA_H__ */
