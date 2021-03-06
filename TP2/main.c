// Intérprete para itree
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "itree.h"

// Definiciones de tipos
typedef union {
  double d;
  /* Se pueden agregar otros en caso de necesitarlo:
   * char  *s;
   * char   c;
   * float  f;
   * */
} arg_t;

typedef struct {
  const char* name;
  void (*func)(arg_t*);
  const char* args;
  const char* doc;
} cmd_t;

// Definiciones de funciones
#define MK_CMD(x) void cmd_ ## x (arg_t*) 
MK_CMD(i);
MK_CMD(e);
MK_CMD(intersec);
MK_CMD(dfs);
MK_CMD(bfs);
MK_CMD(salir);
MK_CMD(help);

arg_t *args_parse(const char *s);

// Datos globales
// La tabla de mapeo
#define CMD(func, params, help) {#func, cmd_ ## func, params, help}
#define CMDS 7
cmd_t dsp_table[CMDS] = {
  CMD(i,"dd","Inserta el intervalo [a,b] en el árbol."),
  CMD(e,"dd","Elimina el intervalo [a,b] del árbol."),
  {"?",cmd_intersec,"dd","Intersecta el intervalo [a,b] con los intervalos del árbol."},
  CMD(dfs,"","Imprime los intervalos del árbol con recorrido primero en profundidad."),
  CMD(bfs,"","Imprime los intervalos del árbol con recorrido primero a lo ancho."),
  CMD(salir,"","Destruye el árbol y termina el programa."),
  CMD(help,"","Visualiza esta ayuda.")
};

// Delimitador
const char *delim = " \n[,];";

// Arbol
ITree arbol;

// Implementación de funciones
/**
 * Parseo de comandos en funciones
 */
void parse(char *cmd) {
  const char* tok = strtok(cmd, delim);
  if(!tok)
    return;

  int i = CMDS;
  while(i--) {
    cmd_t cur = dsp_table[i];
    if(!strcmp(tok, cur.name)) { // Encuentro la función
      arg_t *args = args_parse(cur.args); // Parseo los argumentos
      if(args == NULL && strlen(cur.args))
        return; // Error en el parseo de argumentos
      cur.func(args);
      free(args);
      return;
    }
  }
  puts("Comando incorrecto");
}

/**
 * Parseo de argumentos en tipos
 */
#define ESCAPE {free(args); puts("Argumento(s) incorrecto(s)"); return NULL;}
arg_t *args_parse(const char *s) {
  int argc = strlen(s);
  arg_t *args = malloc(sizeof(arg_t) * argc);
  int i;
  for(i = 0; i < argc; ++i) {
    char *tok;
    switch(s[i]) {
      case 'd':
        tok = strtok(NULL,delim);
        if(!tok)
          ESCAPE; // Si falta algún argumento
        if(sscanf(tok,"%lf", &args[i].d) != 1)
          ESCAPE; // Si falla la conversión a double
        break;
    }
  }
  return args;
}
#undef ESCAPE

int main() {
  char prompt[200];
  strncpy(prompt,">",200);
  
  arbol = itree_crear();
  
  // Lee - Parsea - Ejecuta - Loopea
  char cmd[200];
  while(1) {
    printf("%s ",prompt);
    fflush(stdout);
    
    parse(fgets(cmd,200,stdin));
  }

  return 2;
}

/**
 * Funciones que mapean comandos en funciones de ITree.
 * También controlan los intervalos ingresados.
 */
void cmd_i(arg_t *args) {
  if (validar_intervalo(args[0].d, args[1].d)) { // Si el intervalo es válido
    arbol = itree_insertar(args[0].d, args[1].d, arbol);
  } else {
    printf("El intervalo ingresado no es válido\n");
    return;
  }
}

void cmd_e(arg_t *args) {
  if (validar_intervalo(args[0].d, args[1].d)) { // Si el intervalo es válido
    arbol = itree_eliminar(args[0].d, args[1].d, arbol);
  } else {
    printf("El intervalo ingresado no es válido\n");
    return;
  }
}

void cmd_intersec(arg_t *args) {
  if (validar_intervalo(args[0].d, args[1].d)) { // Si el intervalo es válido
    ITree temp = itree_intersectar(args[0].d, args[1].d, arbol);
    if (itree_empty(temp)) // Si la intersección es vacía
      printf("No\n");
    else {
      printf("Si ");
      mostrar_intervalo(temp);
    }
  } else {
    printf("El intervalo ingresado no es válido\n");
    return;
  }
}

void cmd_dfs(arg_t *args) {
  itree_recorrer_dfs(arbol, ITREE_RECORRIDO_PRE, mostrar_intervalo);
}

void cmd_bfs(arg_t *args) {
  itree_recorrer_bfs(arbol, mostrar_intervalo);
}

void cmd_salir(arg_t *args) {
  itree_destruir(arbol);
  arbol = NULL;
  exit(0);
}

void cmd_help(arg_t *args) {
  puts("Comandos disponibles:");
  int i = CMDS;
  while(i--) {
    cmd_t cmd = dsp_table[i];
    char tmp[100]; // Formateando el buffer para mostrarlo
    snprintf(tmp, 100, "%s(%s)", cmd.name, cmd.args);
    printf("%10s\t- %s\n", tmp, cmd.doc);
  }
}
