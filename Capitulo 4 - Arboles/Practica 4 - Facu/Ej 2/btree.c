#include "btree.h"
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

void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, 
                    FuncionVisitante visit) {
  // Caso base
  if (btree_empty(arbol))
    return;
  
  // Caso recursivo
  switch (orden) {
    // Si el recorrido es preorder
    case BTREE_RECORRIDO_PRE:
      visit(arbol->dato);
      btree_recorrer(arbol->left, orden, visit);
      btree_recorrer(arbol->right, orden, visit);
      break;
    
    // Si el recorrido es inorder
    case BTREE_RECORRIDO_IN:
      btree_recorrer(arbol->left, orden, visit);
      visit(arbol->dato);
      btree_recorrer(arbol->right, orden, visit);
      break;
    
    // Si el recorrido es postorder
    case BTREE_RECORRIDO_POST:
      btree_recorrer(arbol->left, orden, visit);
      btree_recorrer(arbol->right, orden, visit);
      visit(arbol->dato);
      break;
  }
}
