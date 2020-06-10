-La compilación se deberá hacer de la siguiente forma:
gcc -std=c99 -Werror -Wall cola.c itree.c main.c

-Los comandos del intérprete son los siguientes:
Comandos disponibles:
     i [a,b]	- Inserta el intervalo [a,b] en el árbol.
     e [a,b]	- Elimina el intervalo [a,b] del árbol.
     ? [a,b]	- Intersecta el intervalo [a,b] con los intervalos del árbol.
     dfs()		- Imprime los intervalos del árbol con recorrido primero en profundidad.
     bfs()		- Imprime los intervalos del árbol con recorrido primero a lo ancho.
   salir()		- Destruye el árbol y termina el programa.
    help()		- Visualiza esta ayuda.
