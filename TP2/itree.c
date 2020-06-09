#include "itree.h"
#include <stdlib.h>
#include <stdio.h>

ITree itree_crear() {
  return NULL;
}

ITree nodo_nuevo(double ini, double fin) {
  ITree nuevo = malloc(sizeof(ITNodo));
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

ITree itree_insertar(double ini, double fin, ITree tree) {
  /*
  if (ini > fin){                                       
	printf("El intervalo [%f, %f] no es válido.\n", ini, fin);
	return tree;
  }*/
  if (itree_empty(tree)){                                                       // si es vacio, creo el nodo
	tree = nodo_nuevo(ini, fin);
    return tree;                                                                
  }else{
     int comp_intervalo = intervalos_comparar(ini, fin, tree->extremo_izq,      // Insercion normal
                                                        tree->extremo_der);     //  . 
     if (comp_intervalo == -1)                                                  // .
       tree->left = itree_insertar(ini, fin, tree->left);                       // .
     else if (comp_intervalo == 1)                                              // .
       tree->right = itree_insertar(ini, fin, tree->right);                     // .
     else{                                                                      // .
       printf("El intervalo [%f, %f] ya existe.\n", ini, fin);                  // .
       return tree;                                                             // . 
     }                                                             
  }                                                                             
  actualizar_max(tree); 
  actualizar_altura(tree);
                                                                              
  int bf = itree_balance_factor(tree);                                          // Guardo el factores balances
  
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
	  free(tree);
    }else if (itree_empty(tree->right)) {
	  temp = tree->left;
	  free(tree);
    }else{
      temp = minimo_nodo_a_raiz(tree->right);
      temp->left = tree->left;
      free(tree);
      actualizar_max(temp);                                                       // actualizo max una vez enganchado
      temp->altura = 1 + maximo2(itree_altura(temp->left),                        //  Actualizo altura
                             itree_altura(temp->right));
    }
    return temp;
  }
  if (comp_intervalo == -1)
     tree->left = itree_eliminar(ini, fin, tree->left);
  else
     tree->right = itree_eliminar(ini, fin,tree->right);
  actualizar_max(tree);                                                          //  Actualizo max
  tree->altura = 1 + maximo2(itree_altura(tree->left),                           //  Actualizo altura
                             itree_altura(tree->right));
  return tree; 
}

ITree minimo_nodo_a_raiz(ITree tree){
  //if (itree_empty(tree))
  //  return tree;
  if (!(tree->left))
    return tree;
  ITree min = tree->left;
  if (!(min->left)) 
    tree->left = min->right;
  min = minimo_nodo_a_raiz(min);
  min->right = tree;
  actualizar_max(tree);
  tree->altura = 1 + maximo2(itree_altura(tree->left),                           //  Actualizo altura
                             itree_altura(tree->right));
  return min;
}

int itree_altura(ITree arbol) {
  if (itree_empty(arbol))
    return -1;
  else
    return arbol->altura;
}

void actualizar_altura(ITree nodo) {
  nodo->altura = 1 + maximo2(itree_altura(nodo->left), 
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
      visit(arbol->extremo_izq, arbol->extremo_der, arbol->max, arbol->altura);
      itree_recorrer_dfs(arbol->left, orden, visit);
      itree_recorrer_dfs(arbol->right, orden, visit);
      break;
    
    // Si el recorrido es inorder
    case ITREE_RECORRIDO_IN:
      itree_recorrer_dfs(arbol->left, orden, visit);
      visit(arbol->extremo_izq, arbol->extremo_der, arbol->max, arbol->altura);
      itree_recorrer_dfs(arbol->right, orden, visit);
      break;
    
    // Si el recorrido es postorder
    case ITREE_RECORRIDO_POST:
      itree_recorrer_dfs(arbol->left, orden, visit);
      itree_recorrer_dfs(arbol->right, orden, visit);
      visit(arbol->extremo_izq, arbol->extremo_der, arbol->max, arbol->altura);
      break;
  }
}

int intervalos_comparar(double ini1, double fin1, double ini2,double fin2) {
  if (ini1 < ini2)
    return -1;
  if (ini1 > ini2)
    return 1;
  if (ini1 == ini2){
    if (fin1 < fin2)
      return -1;
    if (fin1 > fin2)
      return 1;
    else 
      return 0;
  }
}

void actualizar_max(ITree nodo) {
  if (itree_empty(nodo))
    return;
  if (nodo->left) {
	if (nodo->right) { 
      double aux_max = maximo(nodo->left->max, nodo->right->max);
      nodo->max = maximo(nodo->extremo_der, aux_max);
	}else
	  nodo->max = maximo(nodo->extremo_der, nodo->left->max);
  }else if (nodo->right)
	      nodo->max = maximo(nodo->extremo_der, nodo->right->max);
	    else nodo->max = nodo->extremo_der;
}

float maximo(double a, double b) {
  if(a < b)
    return b;
  else
    return a;
}

int maximo2(int a, int b) {
	if (a < b)
	  return b;
	else
	  return a;
}
