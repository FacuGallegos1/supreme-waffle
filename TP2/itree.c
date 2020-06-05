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
    tree->max_der = fin;
    tree->left = NULL;
    tree->right = NULL;
  }else{
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
    if (itree_empty(tree->left)	&& itree_empty(tree->right)) {
      free(tree);
      return NULL;
    }
    if (!(itree_empty(tree->left)) && itree_empty(tree->right)) {
	  ITree temp1 = tree->left;
	  free(tree);
	  return temp1;
    }
    if (itree_empty(tree->left) && !(itree_empty(tree->right))) {
	  ITree temp2 = tree->right;
	  free(tree);
	  return temp2;
    }else{
      ITree temp3 = minimo_nodo_a_raiz(tree->right);
      temp3->left = tree->left;
      free(tree);
      return temp3;
    }
  }else if (comp_intervalo == -1){
     tree->left = itree_eliminar(ini, fin, tree->left);
     return tree;
   }else{
     tree->right = itree_eliminar(ini, fin,tree->right);
     return tree;
   }
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
      visit(arbol->extremo_izq, arbol->extremo_der);
      itree_recorrer_dfs(arbol->left, orden, visit);
      itree_recorrer_dfs(arbol->right, orden, visit);
      break;
    
    // Si el recorrido es inorder
    case ITREE_RECORRIDO_IN:
      itree_recorrer_dfs(arbol->left, orden, visit);
      visit(arbol->extremo_izq, arbol->extremo_der);
      itree_recorrer_dfs(arbol->right, orden, visit);
      break;
    
    // Si el recorrido es postorder
    case ITREE_RECORRIDO_POST:
      itree_recorrer_dfs(arbol->left, orden, visit);
      itree_recorrer_dfs(arbol->right, orden, visit);
      visit(arbol->extremo_izq, arbol->extremo_der);
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

ITree minimo_nodo_a_raiz(ITree tree){
  if (itree_empty(tree))
    return tree;
  else{
    ITree min = tree;	  
    ITree rec = tree;
    while(rec->left) {
	  if (rec->left->left)
	    rec = rec->left;
	  else{
	    min = rec->left;
	    rec->left = min->right;
        min->right = tree;
      }
    }
    return min;    
  }
}
