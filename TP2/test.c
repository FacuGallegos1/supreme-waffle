#include <stdio.h>
#include <stdlib.h>
#include "itree.h"

void mostrar_intervalo(double ini, double fin, double max) {
  printf("[%f, %f] max = %f\n", ini, fin, max);
}

int main() {
  ITree test = itree_crear();
  test = itree_insertar(1, 3, test);
  test = itree_insertar(0, 2, test);
  test = itree_insertar(-1, 0, test);
  test = itree_insertar(0.5, 1, test);
  test = itree_insertar(2, 4, test);
  test = itree_insertar(1.5, 2.5, test);
  test = itree_insertar(3, 5, test);
  test = itree_insertar(-6, 10, test);
  test = itree_insertar(-0.5, 3, test);
  test = itree_insertar(-0.3, 1, test);
  test = itree_insertar(1, 1.5, test);
  test = itree_insertar(1.3, 3, test);
  test = itree_insertar(2, 2.5, test);
  test = itree_insertar(4, 10, test);
  test = itree_insertar(6, 8, test);
  test = itree_insertar(1, 3, test);
  test = itree_insertar(2, 2.6, test);
  test = itree_insertar(2, 2.4, test);
  test = itree_insertar(2, 2.3, test);
  test = itree_insertar(1.6, 5, test);
  test = itree_insertar(2, 2.35, test);
  
  
  //printf("hola\n");
  //test = itree_eliminar(2, 4, test);
  //printf("hola2\n");
  //test = itree_eliminar(3, 5, test);
  //test = itree_eliminar(0, 2, test);
  test = itree_eliminar(1.5, 2.5, test);
  
  printf("TEST PREORDER\n");
  itree_recorrer_dfs(test, ITREE_RECORRIDO_PRE, mostrar_intervalo);
  printf("TEST INORDER\n");
  itree_recorrer_dfs(test, ITREE_RECORRIDO_IN, mostrar_intervalo);
  printf("TEST POSORDER\n");
  itree_recorrer_dfs(test, ITREE_RECORRIDO_POST, mostrar_intervalo);
  
  itree_destruir(test);
  return 0;
}
