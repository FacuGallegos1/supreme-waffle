#include "btree.h"
#include "pila.h"
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

int btree_handler_es_hoja(void* dato) {
  return btree_es_hoja(btree_cast(dato));
}

void btree_recorrer_it(BTree arbol, BTreeOrdenDeRecorrido orden,
                       FuncionVisitante visit) {
  Pila pila = pila_crear();
  if (!btree_empty(arbol))
    pila = pila_push(pila, arbol);
  while (!pila_is_empty(pila)) {
    // Si encuentro una hoja
    if (btree_handler_es_hoja(pila->ultimo->dato)) {
      visit(btree_get_dato(pila->ultimo->dato));
      pila_pop(pila);
    } else {
      // Saco el dato de la pila sin destruir el mismo, analizo la raíz obtenida
      BTree raiz = btree_cast(pila_top(pila));
      pila_pop(pila);
      switch (orden) {
        // Si el recorrido es preorder
        case BTREE_RECORRIDO_PRE:
          if (!btree_empty(raiz->right))
            pila = pila_push(pila, raiz->right); // Derecha
          if (!btree_empty(raiz->left))
            pila = pila_push(pila, raiz->left);  // Izquierda
          pila = pila_push(pila, raiz);          // Raíz
          break;
    
        // Si el recorrido es inorder
        case BTREE_RECORRIDO_IN:
          if (!btree_empty(raiz->right))
            pila = pila_push(pila, raiz->right); // Derecha
          pila = pila_push(pila, raiz);          // Raíz
          if (!btree_empty(raiz->left))
            pila = pila_push(pila, raiz->left);  // Izquierda
          break;
    
        // Si el recorrido es postorder
        case BTREE_RECORRIDO_POST:
          pila = pila_push(pila, raiz);          // Raíz
          if (!btree_empty(raiz->right))
            pila = pila_push(pila, raiz->right); // Derecha
          if (!btree_empty(raiz->left))
            pila = pila_push(pila, raiz->left);  // Izquierda
          break;
      }
      // Convierto la raíz en una hoja porque sólo me queda procesarla
      raiz->left = NULL;
      raiz->right = NULL;
      /**
       * De esta manera si desde la pila elimino sus subárboles izquierda o
       * derecha, raiz->left y raiz->right no quedan dangling.
       **/
    }
  }
  pila_destruir(pila);
}

