#ifndef __ITREE_H__
#define __ITREE_H__

typedef void (*FuncionVisitante) (double ini, double fin);

typedef enum {
  ITREE_RECORRIDO_IN,
  ITREE_RECORRIDO_PRE,
  ITREE_RECORRIDO_POST
} ITreeOrdenDeRecorrido;


/* no la uso a la estructura */
typedef struct _Intervalo {
  double extremo_izq;
  double extremo_der;
} Intervalo;


typedef struct _ITNodo {
  double extremo_izq;
  double extremo_der;
  double max_der;
  struct _ITNodo *left;
  struct _ITNodo *right;
} ITNodo;

typedef ITNodo *ITree;

/**
 * Crea un árbol de intervalos vacío.
 */
ITree itree_crear();

/**
 * Destruye el árbol de intervalos.
 */
void itree_destruir(ITree nodo);

/**
 * Indica si el árbol es vacío.
 */
int itree_empty(ITree nodo);

/**
 * Inserta un intervalo (válido) en el árbol (y chequea que 
 * siga siendo un árbol AVL - no implementado esto último). 
 */
ITree itree_insertar(double ini, double fin, ITree tree);

/**
 * Elimina un intervalo (válido) en el árbol (y chequea que 
 * siga siendo un árbol AVL - no implementado esto último). 
 */
ITree itree_eliminar(double ini, double fin, ITree root);

/**
 * Determina si un intervalo se intersecta con alguno de los 
 * intervalos del árbol y, en caso afirmativo, retorna un
 * apuntador al nodo correspondiente. 
ITree itree_intersectar(double ini, double fin, ITree root);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void itree_recorrer_dfs(ITree arbol, ITreeOrdenDeRecorrido orden,
                        FuncionVisitante visit);

/**
 * fijate si te sale que creo que hay que usar una cola.
 * No hay ordenes en bfs
 * Creas la cola y le agregas la raiz
 *    1)visitas la raiz
 *    2)encolas el hijo izquierdo
 *    3)encolas el hijo derecho
 *    4)desencolas el primer elemento(la raiz en este primer caso)
 * Ahora haces lo mismo con el nuevo primer elemento de la cola...
 * Cuamdo la cola este vacía, termino el recorrido
 */
void itree_recorrer_bfs(ITree arbol, FuncionVisitante visit); 

#endif /* __ITREE_H__ */
