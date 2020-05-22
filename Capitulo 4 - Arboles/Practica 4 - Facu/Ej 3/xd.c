void btree_recorrer_it(BTree arbol, BTreeOrdenDeRecorrido orden,
                       FuncionVisitante visit) {
  Pila pila = pila_crear();
  BTNodo* nodoActual = arbol;
  while (!btree_empty(nodoActual)) {
    // Si encuentro una hoja
    if (btree_es_hoja(nodoActual)) {
      if (pila_is_empty(pila))
        pila_push(pila, nodoActual);
      // Proceso la hoja antes de destruirla
      visit(nodoActual->dato);
      pila_pop(pila, btree_handler_destruir);
      // Actualizo nodoActual
      if (!pila_is_empty(pila)) {
        nodoActual = btree_cast(pila->ultimo->dato);
      } else {
        nodoActual = NULL;
      }
    } else {
      switch (orden) {
        // Si el recorrido es preorder
        case BTREE_RECORRIDO_PRE:
          if (!btree_empty(nodoActual->right))
            pila = pila_push(pila, nodoActual->right); // Derecha
          if (!btree_empty(nodoActual->left))
            pila = pila_push(pila, nodoActual->left);  // Izquierda
          pila = pila_push(pila, nodoActual);          // Raíz
          break;
    
        // Si el recorrido es inorder
        case BTREE_RECORRIDO_IN:
          if (!btree_empty(nodoActual->right))
            pila = pila_push(pila, nodoActual->right); // Derecha
          pila = pila_push(pila, nodoActual);          // Raíz
          if (!btree_empty(nodoActual->left))
            pila = pila_push(pila, nodoActual->left);  // Izquierda
          break;
    
        // Si el recorrido es postorder
        case BTREE_RECORRIDO_POST:
          pila = pila_push(pila, nodoActual);          // Raíz
          if (!btree_empty(nodoActual->right))
            pila = pila_push(pila, nodoActual->right); // Derecha
          if (!btree_empty(nodoActual->left))
            pila = pila_push(pila, nodoActual->left);  // Izquierda
          break;
      }
      // Corrijo punteros dangling porque sé que voy a eliminar los nodos
      // que ya están en la pila.
      nodoActual->left = NULL;
      nodoActual->right = NULL;
      // Si hay subárbol derecho, lo agrego a la pila
      if (!btree_empty(btree_get_right(pila->ultimo->dato))) {
        pila = pila_push(pila, btree_get_right(pila->ultimo->dato));
        // Corrijo punteros dangling porque sé que voy a eliminar los nodos
        // que ya están en la pila.
        btree_cast(pila->ultimo->dato)->right = NULL;
      }
      // Si hay subárbol izquierdo, lo agrego a la pila
      if (!btree_empty(btree_get_left(pila->ultimo->dato))) {
        pila = pila_push(pila, btree_get_right(pila->ultimo->dato));
        // Corrijo punteros dangling porque sé que voy a eliminar los nodos
        // que ya están en la pila.
        btree_cast(pila->ultimo->dato)->left = NULL;
      }
      /**
       * Con la corrección de punteros dangling dentro del árbol, logro que 
       * cada raíz procesada se agregue a la pila y se convierta en una hoja.
       **/
    }
  }
}




void btree_recorrer_it(BTree arbol, BTreeOrdenDeRecorrido orden,
                       FuncionVisitante visit) {
  Pila pila = pila_crear();
  pila = pila_push(pila, arbol);
  while (!pila_is_empty(pila)) {
    // Si encuentro una hoja
    if (btree_handler_es_hoja(pila->ultimo->dato)) {
      pila_pop(pila, btree_handler_destruir);
    } else {
      // Si hay subárbol derecho, lo agrego a la pila
      if (!btree_empty(btree_get_right(pila->ultimo->dato))) {
        pila = pila_push(pila, btree_get_right(pila->ultimo->dato));
        // Corrijo punteros dangling porque sé que voy a eliminar los nodos
        // que ya están en la pila.
        btree_cast(pila->ultimo->dato)->right = NULL;
      }
      // Si hay subárbol izquierdo, lo agrego a la pila
      if (!btree_empty(btree_get_left(pila->ultimo->dato))) {
        pila = pila_push(pila, btree_get_right(pila->ultimo->dato));
        // Corrijo punteros dangling porque sé que voy a eliminar los nodos
        // que ya están en la pila.
        btree_cast(pila->ultimo->dato)->left = NULL;
      }
      /**
       * Con la corrección de punteros dangling dentro del árbol, logro que 
       * cada raíz procesada se agregue a la pila y se convierta en una hoja.
       **/
    }
  }
}




void btree_recorrer_it(BTree arbol, BTreeOrdenDeRecorrido orden,
                       FuncionVisitante visit) {
  Pila pila = pila_crear();
  if (!btree_empty(arbol))
    pila = pila_push(pila, arbol);
  while (!pila_is_empty(pila)) {
    // Si encuentro una hoja
    if (btree_handler_es_hoja(pila->ultimo->dato)) {
      visit(btree_get_dato(pila->ultimo->dato));
      pila_pop(pila, btree_handler_destruir);
    } else {
      // Saco el dato de la pila sin destruir el mismo, analizo la raíz obtenida
      BTree raiz = btree_cast(pila_pop_2(pila));
      switch (orden) {
        // Si el recorrido es preorder
        case BTREE_RECORRIDO_PRE:
          if (!btree_empty(raiz->right))
            pila = pila_push(pila, raiz->right); // Derecha
          if (!btree_empty(raiz->left))
            pila = pila_push(pila, raiz->left);  // Izquierda
          pila = pila_push(pila, raiz);          // Raíz
          break;
    
        // Si el recorrido es inorder
        case BTREE_RECORRIDO_IN:
          if (!btree_empty(raiz->right))
            pila = pila_push(pila, raiz->right); // Derecha
          pila = pila_push(pila, raiz);          // Raíz
          if (!btree_empty(raiz->left))
            pila = pila_push(pila, raiz->left);  // Izquierda
          break;
    
        // Si el recorrido es postorder
        case BTREE_RECORRIDO_POST:
          pila = pila_push(pila, raiz);          // Raíz
          if (!btree_empty(raiz->right))
            pila = pila_push(pila, raiz->right); // Derecha
          if (!btree_empty(raiz->left))
            pila = pila_push(pila, raiz->left);  // Izquierda
          break;
      }
      // Convierto la raíz en una hoja porque sólo me queda procesarla
      raiz->left = NULL;
      raiz->right = NULL;
      /**
       * De esta manera si desde la pila elimino sus subárboles izquierda o
       * derecha, raiz->left y raiz->right no quedan dangling.
       **/
    }
  }
}
