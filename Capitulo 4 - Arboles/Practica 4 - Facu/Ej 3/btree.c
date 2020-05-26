#include "btree.h"
#include "pila.h"
#include "pilaxbtree.h"
#include <stdlib.h>

BTree btree_crear() {
  return NULL;
}

void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

BTree btree_cast(void* dato) {
  return (BTree)dato;
}

int btree_get_dato(void* dato) {
  return btree_cast(dato)->dato;
}

BTNodo* btree_get_left(void* dato) {
  return btree_cast(dato)->left;
}

BTNodo* btree_get_right(void* dato) {
  return btree_cast(dato)->right;
}

void btree_handler_destruir(void* dato) {
  btree_destruir(btree_cast(dato));
}

int btree_empty(BTree nodo) {
  return nodo == NULL;
}

BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(BTNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

void btree_recorrer_rec(BTree arbol, BTreeOrdenDeRecorrido orden, 
                        FuncionVisitante visit) {
  // Caso base
  if (btree_empty(arbol))
    return;
  
  // Caso recursivo
  switch (orden) {
    // Si el recorrido es preorder
    case BTREE_RECORRIDO_PRE:
      visit(arbol->dato);
      btree_recorrer_rec(arbol->left, orden, visit);
      btree_recorrer_rec(arbol->right, orden, visit);
      break;
    
    // Si el recorrido es inorder
    case BTREE_RECORRIDO_IN:
      btree_recorrer_rec(arbol->left, orden, visit);
      visit(arbol->dato);
      btree_recorrer_rec(arbol->right, orden, visit);
      break;
    
    // Si el recorrido es postorder
    case BTREE_RECORRIDO_POST:
      btree_recorrer_rec(arbol->left, orden, visit);
      btree_recorrer_rec(arbol->right, orden, visit);
      visit(arbol->dato);
      break;
  }
}

int btree_es_hoja(BTNodo* nodo) {
  if (btree_empty(nodo)) {
    return 0;
  } else {
    if ((nodo->left == NULL) && (nodo->right == NULL)) {
      return 1;
    } else {
      return 0;
    }
  }
}

void btree_recorrer_it(BTree arbol, BTreeOrdenDeRecorrido orden,
                       FuncionVisitante visit) {
  Pila pila = pila_crear();
  if (!btree_empty(arbol)) {
    PilaXBTree pb = pb_crear(arbol, 0);
    if (btree_es_hoja(arbol)) {
      pb->esDestruible = 1;
    }
    pila = pila_push(pila, pb);
  }
  while (!pila_is_empty(pila)) {
    // Si encuentro un nodo destruible
    if (pb_cast(pila->ultimo->dato)->esDestruible) {
      visit(btree_get_dato(pb_cast(pila->ultimo->dato)->nodo));
      pb_destruir(pb_cast(pila->ultimo->dato));
      pila_pop(pila);
    } else {
      // Saco el dato de la pila, analizo la raíz obtenida
      BTree raiz = pb_cast(pila->ultimo->dato)->nodo;
      pb_destruir(pb_cast(pila->ultimo->dato));
      pila_pop(pila);
      // De ahora en más, la raíz va a ser destruible
      PilaXBTree pb = pb_crear(raiz, 1);
      switch (orden) {
        // Si el recorrido es preorder
        case BTREE_RECORRIDO_PRE:
          if (!btree_empty(raiz->right))
            pila = pila_push(pila, pb_crear(raiz->right, 0)); // Derecha
          if (!btree_empty(raiz->left))
            pila = pila_push(pila, pb_crear(raiz->left, 0));  // Izquierda
          pila = pila_push(pila, pb);                         // Raíz
          break;
    
        // Si el recorrido es inorder
        case BTREE_RECORRIDO_IN:
          if (!btree_empty(raiz->right))
            pila = pila_push(pila, pb_crear(raiz->right, 0)); // Derecha
          pila = pila_push(pila, pb);                         // Raíz
          if (!btree_empty(raiz->left))
            pila = pila_push(pila, pb_crear(raiz->left, 0));  // Izquierda
          break;
    
        // Si el recorrido es postorder
        case BTREE_RECORRIDO_POST:
          pila = pila_push(pila, pb);                         // Raíz
          if (!btree_empty(raiz->right))
            pila = pila_push(pila, pb_crear(raiz->right, 0)); // Derecha
          if (!btree_empty(raiz->left))
            pila = pila_push(pila, pb_crear(raiz->left, 0));  // Izquierda
          break;
      }
    }
  }
  pila_destruir(pila);
}
