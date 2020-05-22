#include "btree.h"
#include "funciones.h"
#include <stdlib.h>

int btree_suma_elementos(BTree arbol) {
  // Caso base
  if (btree_empty(arbol)) {
    return 0;
  }
  
  // Caso recursivo
  
  // Sumo los elementos a la izquierda
  int izq = btree_suma_elementos(arbol->left);
  
  // Sumo los elementos a la derecha
  int der = btree_suma_elementos(arbol->right);
  
  // Devuelvo la suma de izq, der y raiz
  return izq + der + arbol->dato;
  
  /**
   * El comportamiento de esta función es recursivo. También recorro el árbol 
   * en postorder, ya que para sumarlos primero proceso los dos hijos de cada 
   * nodo antes de la raíz.
   **/
}

int btree_cant_nodos(BTree arbol) {
  /**
   * -no sé si debería contar los nodos 'externos' o no...
   * (Actualmente no lo hago)
   **/
  // Caso base
  if (btree_empty(arbol)) {
    return 0;
  }
  
  // Caso recursivo
  
  // Cuento los nodos a la izquierda
  int izq = btree_cant_nodos(arbol->left);
  
  // Cuento los nodos a la derecha
  int der = btree_cant_nodos(arbol->right);
  
  // Devuelvo la cantidad de nodos del árbol, contando la raíz
  return izq + der + 1;
  
  /**
   * El comportamiento de esta función es recursivo. También recorro el árbol 
   * en postorder, ya que para contarlos primero proceso los dos hijos de cada 
   * nodo antes de la raíz.
   **/
}

int btree_altura(BTree arbol) {
  // Caso base
  if (btree_empty(arbol)) {
    return -1;
  }
  
  // Caso recursivo
  
  // Calculo la altura del subárbol izquierdo
  int izq = btree_altura(arbol->left);
  // Calculo la altura del subárbol derecho
  int der = btree_altura(arbol->right);
  
  // Devuelvo la mayor altura
  if (izq >= der) {
    return izq + 1;
  } else {
    return der + 1;
  }
  
  /**
   * El comportamiento de esta función es recursivo.
   * En cada recursión calculo la altura del subárbol en cuestión. Luego 
   * devuelvo la altura del subárbol más alto + 1.
   * Uso el -1 para indicar que tomé un árbol vacío.
   **/
}
