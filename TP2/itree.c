#include "itree.h"
#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

ITree itree_crear() {
  return NULL;
}

ITNodo* nodo_nuevo(double ini, double fin) {
  ITNodo* nuevo = malloc(sizeof(ITNodo));
  nuevo->extremo_izq = ini;
  nuevo->extremo_der = fin;
  nuevo->max = fin;
  nuevo->altura = 0;
  nuevo->left = NULL;
  nuevo->right = NULL;
  return nuevo;
}

void itree_destruir(ITree nodo) {
  if (nodo != NULL) {
    itree_destruir(nodo->left);
    itree_destruir(nodo->right);
    free(nodo);
  }
}

int itree_empty(ITree nodo) {
  return nodo == NULL;
}

ITree itree_v_insertar(double ini, double fin, ITree tree) {
  if (ini > fin) {                                       
	printf("El intervalo [%f, %f] no es válido.\n", ini, fin);
	return tree;
  }else
    return itree_insertar(ini, fin, tree);
}

ITree itree_insertar(double ini, double fin, ITree tree) {
  if (itree_empty(tree)) {                                                      // si es vacio, creo el nodo,
    tree = nodo_nuevo(ini, fin);                                                // caso base
    return tree;                                                                
  }
  int comp_intervalo = intervalos_comparar(ini, fin, tree->extremo_izq,         // Insercion normal,
                                                     tree->extremo_der);        // caso recursivo
  if (comp_intervalo == -1)                                                     // .
    tree->left = itree_insertar(ini, fin, tree->left);                          // .
  else if (comp_intervalo == 1)                                                 // .
    tree->right = itree_insertar(ini, fin, tree->right);                        // .
  else {                                                                        // .
    printf("El intervalo [%lf, %lf] ya existe.\n", ini, fin);                   // .
    return tree;                                                                // .
  }                                                             
                                                                             
  actualizar_max(tree);
  actualizar_altura(tree);
  
  int bf = itree_balance_factor(tree);                                          // Guardo el factor balance
  
  // acá se podría poner bf perteneciente a {-1; 1}
  
  if (bf < -1 && intervalos_comparar(ini, fin, tree->left->extremo_izq,         // caso izq izq
                                              tree->left->extremo_der) == -1)   
    return rotar_a_derecha(tree);
  
  if (bf < -1 && intervalos_comparar(ini, fin, tree->left->extremo_izq,         // caso izq der
                                              tree->left->extremo_der) == 1) {
    tree->left = rotar_a_izquierda(tree->left);
    return rotar_a_derecha(tree);
  }
  
  if (bf > 1 && intervalos_comparar(ini, fin, tree->right->extremo_izq,         // caso der der
                                              tree->right->extremo_der) == 1) 
    return rotar_a_izquierda(tree);
  
  if (bf > 1 && intervalos_comparar(ini, fin, tree->right->extremo_izq,         // caso der izq
                                              tree->right->extremo_der) == -1) {
    tree->right = rotar_a_derecha(tree->right);
    return rotar_a_izquierda(tree);
  }
  
  return tree;
}

ITree itree_v_eliminar(double ini, double fin, ITree tree) {
  if (ini > fin) {                                       
	printf("El intervalo [%f, %f] no es válido.\n", ini, fin);
	return tree;
  }else
    return itree_eliminar(ini, fin, tree);
}

ITree itree_eliminar(double ini, double fin, ITree tree) {
  if (itree_empty(tree))
    return tree;
  // guardo el resutado de la comparación
  int comp_intervalo = intervalos_comparar(ini, fin, tree->extremo_izq, 
                                                     tree->extremo_der);
  if (comp_intervalo == 0) {
    //Si este es el nodo a eliminar, hay tres casos distintos posibles
    ITree temp;
    if (itree_empty(tree->left)) {
	  temp = tree->right;
    }else if (itree_empty(tree->right)) {
	  temp = tree->left;
    }else{
      temp = minimo_nodo_a_raiz(tree->right);
      temp->left = tree->left;
      actualizar_max(temp);                                                     // Actualizo max una vez enganchado
      actualizar_altura(temp);                                                  // Actualizo altura
    }
    free(tree);
    return temp;
  }
  if (comp_intervalo == -1)
     tree->left = itree_eliminar(ini, fin, tree->left);
  else
     tree->right = itree_eliminar(ini, fin,tree->right);
  
  actualizar_max(tree);                                                         // Actualizo max
  actualizar_altura(tree);                                                      // Actualizo altura
  
  int bf = itree_balance_factor(tree);                                          // Guardo el factor balance
  
  if (bf < -1 && itree_balance_factor(tree->left) <= 0)                         // caso izq izq
    return rotar_a_derecha(tree);
  
  if (bf < -1 && itree_balance_factor(tree->left) > 0) {                        // caso izq der
    tree->left = rotar_a_izquierda(tree->left);
    return rotar_a_derecha(tree);
  }
  
  if (bf > 1 && itree_balance_factor(tree->right) >= 0)                         // caso der der
    return rotar_a_izquierda(tree);
  
  if (bf > 1 && itree_balance_factor(tree->right) < 0) {                        // caso der izq
    tree->right = rotar_a_derecha(tree->right);
    return rotar_a_izquierda(tree);
  }
  
  return tree; 
}

ITree itree_v_intersectar(double ini, double fin, ITree tree) {
  if (ini > fin) {                                       
	printf("El intervalo [%f, %f] no es válido.\n", ini, fin);
	return tree;
  }else
    return itree_intersectar(ini, fin, tree);
}

ITree itree_intersectar(double ini, double fin, ITree tree) {
  printf("Llegué a [%lf, %lf]\n", tree->extremo_izq, tree->extremo_der);
  if (tree->max < ini) // El intervalo está a la derecha del máximo
    return NULL;
  if (fin < tree->extremo_izq) // El intervalo está a la izquierda de la raíz
    return itree_intersectar(ini, fin, tree->left);
  if (tree->extremo_der < ini) { // El intervalo está a la derecha de la raíz
    if (tree->left->max < ini)  // Si el máximo del hijo izq no llega al interv.
      return itree_intersectar(ini, fin, tree->right); // Busco derecha
    else                                               // sino
      return itree_intersectar(ini, fin, tree->left);  // busco izquierda
  }
  return tree; // El intervalo interseca a la raíz actual
}

ITree minimo_nodo_a_raiz(ITree tree){
  if (itree_empty(tree->left))
    return tree;
  ITree min = tree->left;
  min = minimo_nodo_a_raiz(min);
  
  tree->left = min->right;
  min->right = tree;
  actualizar_max(tree);
  actualizar_altura(tree);
  
  int bf = itree_balance_factor(tree);
  
  if (bf < -1 && itree_balance_factor(tree->left) <= 0)                        // caso izq izq
    min->right = rotar_a_derecha(tree);
  else if (bf < -1 && itree_balance_factor(tree->left) > 0) {                  // caso izq der
    tree->left = rotar_a_izquierda(tree->left);
    min->right = rotar_a_derecha(tree);
  }
  else if (bf > 1 && itree_balance_factor(tree->right) >= 0)                   // caso der der
    min->right = rotar_a_izquierda(tree);
  else if (bf > 1 && itree_balance_factor(tree->right) < 0) {                  // caso der izq
    tree->right = rotar_a_derecha(tree->right);
    min->right = rotar_a_izquierda(tree);
  }
  
  return min;
}

int itree_altura(ITree arbol) {
  if (itree_empty(arbol))
    return -1;
  else
    return arbol->altura;
}

void actualizar_altura(ITree nodo) {
  nodo->altura = 1 + maximo_i(itree_altura(nodo->left), 
                              itree_altura(nodo->right));
}

int itree_balance_factor(ITree nodo) {
  return itree_altura(nodo->right) - itree_altura(nodo->left);
}

ITree rotar_a_izquierda(ITree tree) {
  ITree nuevaRaiz = tree->right;
  ITree temp = tree->right->left;
  
  // Hago la rotación
  tree->right = temp;            
  nuevaRaiz->left = tree;
  
  // actualizo datos
  actualizar_max(tree);
  actualizar_altura(tree);
  actualizar_max(nuevaRaiz);
  actualizar_altura(nuevaRaiz);
  
  return nuevaRaiz;

}

ITree rotar_a_derecha(ITree tree) {
  ITree nuevaRaiz = tree->left;
  ITree temp = tree->left->right;
  
  // Hago la rotación
  tree->left = temp;            
  nuevaRaiz->right = tree;
  
  // actualizo datos
  actualizar_max(tree);
  actualizar_altura(tree);
  actualizar_max(nuevaRaiz);
  actualizar_altura(nuevaRaiz);
  
  return nuevaRaiz;
}
  


void itree_recorrer_dfs(ITree arbol, ITreeOrdenDeRecorrido orden, 
                        FuncionVisitante visit) {
  // Caso base
  if (itree_empty(arbol))
    return;
  
  // Caso recursivo
  switch (orden) {
    // Si el recorrido es preorder
    case ITREE_RECORRIDO_PRE:
      visit(arbol);
      itree_recorrer_dfs(arbol->left, orden, visit);
      itree_recorrer_dfs(arbol->right, orden, visit);
      break;
    
    // Si el recorrido es inorder
    case ITREE_RECORRIDO_IN:
      itree_recorrer_dfs(arbol->left, orden, visit);
      visit(arbol);
      itree_recorrer_dfs(arbol->right, orden, visit);
      break;
    
    // Si el recorrido es postorder
    case ITREE_RECORRIDO_POST:
      itree_recorrer_dfs(arbol->left, orden, visit);
      itree_recorrer_dfs(arbol->right, orden, visit);
      visit(arbol);
      break;
  }
}

void itree_recorrer_bfs(ITree arbol, FuncionVisitante visit) {
  if (itree_empty(arbol)) {
    printf("El árbol está vacío\n");
    return;
  }
  Cola cola = cola_crear();
  cola_encolar(cola, arbol); // Encolo la raíz
  while(!cola_es_vacia(cola)) {
    ITree primero = (ITree)cola_primero(cola); // Me posiciono en el 1ero
    if (!itree_empty(primero->left)) // Si tiene hijo izq, lo encolo
      cola_encolar(cola, primero->left);
    if (!itree_empty(primero->right)) // Si tiene hijo der, lo encolo
    cola_encolar(cola, primero->right);
    visit(primero); // Visito el 1ero
    cola_desencolar(cola); // Lo saco de la cola
  }
  cola_destruir(cola);
}

int intervalos_comparar(double ini1, double fin1, double ini2, double fin2) {
  if (ini1 < ini2)
    return -1;
  if (ini1 > ini2)
    return 1;
  if (ini1 == ini2) { // En caso de empate, me fijo en los extremos derechos
    if (fin1 < fin2)
      return -1;
    if (fin1 > fin2)
      return 1;
  }
  return 0; // Si llega a este return los intervalos son iguales
}

void actualizar_max(ITree nodo) {
  if (itree_empty(nodo))
    return;
  if (nodo->left) {
    if (nodo->right) {
      double aux_max = maximo_d(nodo->left->max, nodo->right->max);
      nodo->max = maximo_d(nodo->extremo_der, aux_max);
    } else
      nodo->max = maximo_d(nodo->extremo_der, nodo->left->max);
  } else if (nodo->right)
      nodo->max = maximo_d(nodo->extremo_der, nodo->right->max);
    else nodo->max = nodo->extremo_der;
}

double maximo_d(double a, double b) {
  if(a < b)
    return b;
  else
    return a;
}

int maximo_i(int a, int b) {
  if (a < b)
    return b;
  else
    return a;
}
