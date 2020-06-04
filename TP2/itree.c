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
     if (ini == tree->extremo_izq ){
	   if (fin == tree->extremo_der){
	     printf("El intervalo [%f, %f] ya existe.\n", ini, fin);
       }else{
	     if (fin < tree->extremo_der){
	     tree->left = itree_insertar(ini, fin, tree->left);
	     }else{
		   tree->right = itree_insertar(ini, fin, tree->right);
		 }
	   }
     }else{
	   if (ini < tree->extremo_izq ){
	     tree->left = itree_insertar(ini, fin, tree->left);
	   }else{
	     tree->right = itree_insertar(ini, fin, tree->right);
	   }
     }
  }
	    
  return tree;
}

/*
ITree itree_eliminar(double ini, double fin, ITree tree) {
  if (itree_empty(tree))
  else{
     if (ini == tree->extremo_izq && fin == tree->extremo_der){
	   if (!(tree->extremo_izq) && !(tree->extremo_der)){
	     free tree;
       }else{
	     if (fin < tree->extremo_der){
	     tree->left = itree_insertar(ini, fin, tree->left);
	     }else{
		   tree->right = itree_insertar(ini, fin, tree->right);
		 }
	   }
     }else{
	   if (ini < tree->extremo_izq ){
	     tree->left = itree_insertar(ini, fin, tree->left);
	   }else{
	     tree->right = itree_insertar(ini, fin, tree->right);
	   }
     }
  }
	    
  return tree;
}
*/

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

