#ifndef __PILAXBTREE_H__
#define __PILAXBTREE_H__

typedef struct _PilaXBTree {
  BTNodo* nodo;
  int esDestruible;
}* PilaXBTree;

/**
 * Castea un pilaxbtree.
 **/
PilaXBTree pb_cast(void* dato);

/**
 * Crea un pilaxbtree.
 **/
PilaXBTree pb_crear(BTNodo* nodo, int esDestruible);

/**
 * Destruye un pilaxbtree.
 **/
void pb_destruir(PilaXBTree pb);

#endif /* __PILAXBTREE_H__ */
