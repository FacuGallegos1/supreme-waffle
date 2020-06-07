#include "itree.h"
#include <stdlib.h>
#include <stdio.h>

ITree itree_crear() {
  return NULL;
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
	return root;
  }*/
  if (itree_empty(tree)){
	tree = malloc(sizeof(ITNodo));
    tree->extremo_izq = ini;
    tree->extremo_der = fin;
    tree->max = fin;
    tree->left = NULL;
    tree->right = NULL;
  }else{
     tree->max = maximo(fin, tree->max);
     int comp_intervalo = intervalos_comparar(ini, fin, tree->extremo_izq, 
                                                        tree->extremo_der);
     if (comp_intervalo == -1)
       tree->left = itree_insertar(ini, fin, tree->left);
     else if (comp_intervalo == 1)
       tree->right = itree_insertar(ini, fin, tree->right);
     else
       printf("El intervalo [%f, %f] ya existe.\n", ini, fin);
  }
  return tree;
}


ITree itree_eliminar(double ini, double fin, ITree tree) {
  if (itree_empty(tree))
    return tree;
  int comp_intervalo = intervalos_comparar(ini, fin, tree->extremo_izq, 
                                                     tree->extremo_der);
  if (comp_intervalo == 0) {
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
      actualizar_max(temp);
    }
    return temp;
  }
  if (comp_intervalo == -1)
     tree->left = itree_eliminar(ini, fin, tree->left);
  else
     tree->right = itree_eliminar(ini, fin,tree->right);
  actualizar_max(tree);
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
  return min;
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
      visit(arbol->extremo_izq, arbol->extremo_der, arbol->max);
      itree_recorrer_dfs(arbol->left, orden, visit);
      itree_recorrer_dfs(arbol->right, orden, visit);
      break;
    
    // Si el recorrido es inorder
    case ITREE_RECORRIDO_IN:
      itree_recorrer_dfs(arbol->left, orden, visit);
      visit(arbol->extremo_izq, arbol->extremo_der, arbol->max);
      itree_recorrer_dfs(arbol->right, orden, visit);
      break;
    
    // Si el recorrido es postorder
    case ITREE_RECORRIDO_POST:
      itree_recorrer_dfs(arbol->left, orden, visit);
      itree_recorrer_dfs(arbol->right, orden, visit);
      visit(arbol->extremo_izq, arbol->extremo_der, arbol->max);
      break;
  }
}

int itree_altura(ITree arbol) {
  if (itree_empty(arbol)) {
    return -1;
  }
  int altura_izq = itree_altura(arbol->left);
  int altura_der = itree_altura(arbol->right);
  if (altura_izq > altura_der) {
    return altura_izq + 1;
  } else {
    return altura_der + 1;
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
  }else{
	  if (nodo->right)
	    nodo->max = maximo(nodo->extremo_der, nodo->right->max);
	}
}

float maximo(double a, double b) {
  if(a < b)
    return b;
  else
    return a;
}
