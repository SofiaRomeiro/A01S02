#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "list.h"
#include "input.h"

#define ROOT '/'
#define MAX_BUFFER 65535
#define MAX_COMMAND_LEN 6
#define SPACE ' ' || '\t'
#define eq_int(A,B) (A==B)
#define eq_char(A,B) !(strcmp(A,B))


char *read_line();
char *read_command(char *buffer);
int aux();

enum commands {HELP, QUIT, SET, PRINT, FIND, LIST, SEARCH, DELETE, NONE};




int main() {
  /*  tree_node_s root = treeConstructor(); */
    int quit=0;
    int command;

    while (!quit) {

        command = aux();

        switch (command) {
            case HELP:
                printf("help: Imprime os comandos disponíveis.\n");
                printf("quit: Termina o programa.\n");
                printf("set: Adiciona ou modifica o valor a armazenar.\n");
                printf("print: Imprime todos os caminhos e valores.\n");
                printf("find: Imprime o valor armazenado.\n");
                printf("list: Lista todos os componentes imediatos de um sub-caminho.\n");
                printf("search: Procura o caminho dado um valor.\n");
                printf("delete: Apaga um caminho e todos os subcaminhos.\n");
                break;

            case QUIT:
                quit = 1;
                break;
            
            case SET:
                /* TODO mandar o path bem feitinho para o add */
                printf("set\n");
                break;
            
            case PRINT:
                printf("print\n");
                break;

            case FIND:
                printf("find\n");
                break;

            case LIST:
                printf("list\n");
                break;

            case SEARCH:
                printf("search\n");
                break;
            
            case DELETE:
                printf("delete\n");
                break;            
        }
    }      

    return 0;
}

int aux() {
    char command[MAX_COMMAND_LEN+1];
    char c;
    int i=0;
    while ((c=getchar()) != EOF && c != ' ' && c!= '\n') {
        command[i++] = c;
    }
    command[i] = '\0';

    if (eq_char(command, "help")) {
        return HELP;        
    }
    else if (eq_char(command, "quit")) {
        return QUIT;
    }
    else if (eq_char(command, "set")) {
        return SET;
    }
    else if (eq_char(command, "print")) {
        return PRINT;
    }
    else if (eq_char(command, "find")) {
        return FIND;
    }
    else if (eq_char(command, "list")) {
        return LIST;
    }
    else if (eq_char(command, "search")) {
        return SEARCH;
    }
    else if (eq_char(command, "delete")) {
        return DELETE;
    }
    return NONE;
}

