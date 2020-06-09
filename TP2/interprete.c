// Intérprete para itree
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// Type definitions
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

#define MK_CMD(x) void cmd_ ## x (arg_t*)
// Functions definitions
MK_CMD(i);
MK_CMD(e);
MK_CMD(intersec);
MK_CMD(dfs);
MK_CMD(bfs);
MK_CMD(salir);
MK_CMD(help);

arg_t *args_parse(const char *s);

//The dispatch table
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

const char *delim = " \n[,];";
void parse(char *cmd) {
  const char* tok = strtok(cmd, delim);
  if(!tok)
    return;

  int i = CMDS;
  while(i--) {
    cmd_t cur = dsp_table[i];
    if(!strcmp(tok, cur.name)) {
      arg_t *args = args_parse(cur.args);
      if(args == NULL && strlen(cur.args))
        return; // Error in argument parsing
      cur.func(args);
      free(args);
      return;
    }
  }
  puts("Command Not Found");
}

#define ESCAPE {free(args); puts("Bad Argument(s)"); return NULL;}
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

  // Read Parse Exec Loop
  char cmd[200];
  while(1) {
    printf("%s ",prompt);
    fflush(stdout);

    parse(fgets(cmd,200,stdin));
  }

  return 2;
}

void cmd_i(arg_t *args) {
  printf("Acá iría el insertar\n");
  printf("args[0].d: %lf, args[1].d: %lf\n", args[0].d, args[1].d);
}
void cmd_e(arg_t *args) {
  printf("Acá iría el eliminar\n");
  printf("args[0].d: %lf, args[1].d: %lf\n", args[0].d, args[1].d);
}
void cmd_intersec(arg_t *args) {
  printf("Acá iría el intersectar\n");
  printf("args[0].d: %lf, args[1].d: %lf\n", args[0].d, args[1].d);
}
void cmd_dfs(arg_t *args) {printf("Acá iría el dfs\n");}
void cmd_bfs(arg_t *args) {printf("Acá iría el bfs\n");}
void cmd_salir(arg_t *args) {exit(0);}
void cmd_help(arg_t *args) {
  puts("Available Commands:");
  int i = CMDS;
  while(i--) {
    cmd_t cmd = dsp_table[i];
    char tmp[100]; // Formatting buffer
    snprintf(tmp,100,"%s(%s)",cmd.name,cmd.args);
    printf("%10s\t- %s\n",tmp,cmd.doc);
  }
}
