#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "pila.h"

static void imprimir_entero(int data) {
  printf("%d ", data);
}

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
  
  printf("Función recursiva:\n");
  printf("Recorrido preorder:\n");
  btree_recorrer_rec(A, BTREE_RECORRIDO_PRE, imprimir_entero);
  puts("");
  printf("Recorrido inorder:\n");
  btree_recorrer_rec(A, BTREE_RECORRIDO_IN, imprimir_entero);
  puts("");
  printf("Recorrido postorder:\n");
  btree_recorrer_rec(A, BTREE_RECORRIDO_POST, imprimir_entero);
  puts("");
  
  printf("Función iterativa:\n");
  printf("Recorrido preorder:\n");
  //btree_recorrer_it(A, BTREE_RECORRIDO_PRE, imprimir_entero);
  puts("");
  printf("Recorrido inorder:\n");
  //btree_recorrer_it(A, BTREE_RECORRIDO_IN, imprimir_entero);
  puts("");
  printf("Recorrido postorder:\n");
  btree_recorrer_it(A, BTREE_RECORRIDO_POST, imprimir_entero);
  puts("");
  
  btree_destruir(A); // No hace nada pero tampoco rompe nada

  return 0;
}
