#ifndef __PILAXBTREE_H__
#define __PILAXBTREE_H__

typedef struct _PilaXBTree {
  BTNodo* nodo;
  int esDestruible;
} PilaXBTree;

/**
 * Castea un pilaxbtree.
 **/
PilaXBTree pb_cast(void* dato);

#endif /* __PILAXBTREE_H__ */
