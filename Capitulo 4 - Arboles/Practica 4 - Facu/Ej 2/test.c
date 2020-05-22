#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "funciones.h"

int main() {
  BTree E = btree_unir(5, btree_crear(), btree_crear());
  BTree D = btree_unir(4, btree_crear(), E);
  BTree C = btree_unir(3, btree_crear(), btree_crear());
  BTree B = btree_unir(2, C, D);
  BTree J = btree_unir(10, btree_crear(), btree_crear());
  BTree I = btree_unir(9, btree_crear(), btree_crear());
  BTree H = btree_unir(8, I, J);
  BTree G = btree_unir(7, H, btree_crear());
  BTree F = btree_unir(6, btree_crear(), G);
  BTree A = btree_unir(1, B, F);
  
  printf("Suma de elementos: %d \n", btree_suma_elementos(A));
  printf("Cantidad de nodos: %d \n", btree_cant_nodos(A));
  printf("Altura: %d \n", btree_altura(A));
  
  btree_destruir(A);

  return 0;
}
