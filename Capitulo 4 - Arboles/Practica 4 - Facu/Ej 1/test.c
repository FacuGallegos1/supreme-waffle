#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

static void imprimir_entero(int data) {
  printf("%d ", data);
}

int main() {
  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);
  
  printf("Recorrido postorder:\n");
  btree_recorrer(raiz, BTREE_RECORRIDO_POST, imprimir_entero);
  puts("");
  printf("Recorrido preorder:\n");
  btree_recorrer(raiz, BTREE_RECORRIDO_PRE, imprimir_entero);
  puts("");
  printf("Recorrido inorder:\n");
  btree_recorrer(raiz, BTREE_RECORRIDO_IN, imprimir_entero);
  puts("");
  
  btree_destruir(raiz);

  return 0;
}
