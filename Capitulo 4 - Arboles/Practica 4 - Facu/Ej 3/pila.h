#ifndef __PILA_H__
#define __PILA_H__

typedef void (*Destruir) (void* dato);

typedef struct _GPNodo {
  void* dato;
  struct _GPNodo* ant;
} GPNodo;

typedef struct _Pila {
  GPNodo* ultimo;
} *Pila;

/**
 * Devuelve una pila vacía.
 */
Pila pila_crear();

/**
 * Determina si la pila es vacía.
 */
int pila_is_empty(Pila pila);

/**
 * Inserta un elemento en el tope de la Pila.
 */
Pila pila_push(Pila pila, void* dato);

/**
 * Retorna el dato que se encuentre en el tope de la Pila, 
 * pero sin eliminar ni el nodo ni el dato de ésta.
 */
void* pila_top(Pila pila);

/**
 * Elimina el nodo que se encuentra en el tope de la Pila. Pero sin destruir
 * el dato.
 */
void pila_pop(Pila pila);

/**
 * Elimina el elemento que se encuentra en el tope de la Pila. (Destruye todo).
 */
Pila pila_pop_d(Pila pila, Destruir d);

/**
 * Destrucción de la pila.
 */
void pila_destruir(Pila pila);

/**
 * Destrucción completa de la pila.
 */
void pila_destruir_d(Pila pila, Destruir d);

#endif /* __PILA_H__ */
