#ifndef __BTREE_H__
#define __BTREE_H__

typedef void (*FuncionVisitante) (int dato);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
} BTNodo;

typedef BTNodo *BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destrucción del árbol.
 */
void btree_destruir(BTree nodo);

/* -Handlers de btree a void*- */

/**
 * Casteo un árbol.
 */
BTree btree_cast(void* dato);

/**
 * Obtengo dato.
 */
int btree_get_dato(void* dato);

/**
 * Obtengo left.
 */
BTNodo* btree_get_left(void* dato);

/**
 * Obtengo right.
 */
BTNodo* btree_get_right(void* dato);

/**
 * Casteo un árbol y lo destruyo.
 */
void btree_handler_destruir(void* dato);

/**
 * Casteo un árbol e indico si es hoja.
 */
int btree_handler_es_hoja(void* dato);

/* -Handlers de btree a void*- */

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Indica si el árbol es una hoja.
 */
int btree_es_hoja(BTNodo* nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right);

/**
 * Recorrido del arbol, utilizando la funcion pasada. Manera recursiva.
 */
void btree_recorrer_rec(BTree arbol, BTreeOrdenDeRecorrido orden,
                        FuncionVisitante visit);

/**
 * Recorrido del arbol, utilizando la funcion pasada. Manera iterativa.
 */
void btree_recorrer_it(BTree arbol, BTreeOrdenDeRecorrido orden,
                       FuncionVisitante visit);

#endif /* __BTREE_H__ */
