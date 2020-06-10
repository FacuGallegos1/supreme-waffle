#include <stdio.h>
#include <stdlib.h>
#include "itree.h"

int main() {
  ITree test = itree_crear();
  test = itree_insertar(1, 3, test);
  test = itree_insertar(0, 2, test);
  test = itree_insertar(-1, 0, test);
  test = itree_insertar(0.5, 1, test);
  test = itree_insertar(2, 4, test);
  test = itree_insertar(1.5, 2.5, test);
  test = itree_insertar(3, 5, test);
  test = itree_insertar(-6, 9, test);
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
  
  test = itree_eliminar(2, 4, test);
  test = itree_eliminar(3, 5, test);
  test = itree_eliminar(0, 2, test);
  test = itree_eliminar(-0.3, 1, test);
  test = itree_eliminar(1.5, 2.5, test);
  
  printf("TEST PREORDER\n");
  itree_recorrer_dfs(test, ITREE_RECORRIDO_PRE, mostrar_intervalo);
  
  printf("TEST bfs\n");
  itree_recorrer_bfs(test, mostrar_intervalo);
  
  //printf("TEST INORDER\n");
  //itree_recorrer_dfs(test, ITREE_RECORRIDO_IN, mostrar_intervalo);
  //printf("TEST POSORDER\n");
  //itree_recorrer_dfs(test, ITREE_RECORRIDO_POST, mostrar_intervalo);
  
  ITree a = itree_intersectar(2.1, 2.3, test);
  if (!itree_empty(a))
    mostrar_intervalo(a);
  else
    printf("No se encontró intersec/c [2.1, 2.3]\n");
  ITree b = itree_intersectar(7, 7.1, test);
  if (!itree_empty(b))
    mostrar_intervalo(b);
  else
    printf("No se encontró intersec/c [7, 7.1]\n");
  
  itree_destruir(test);
  return 0;
}
