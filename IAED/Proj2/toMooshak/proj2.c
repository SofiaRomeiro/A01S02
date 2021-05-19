#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"

#define ROOT '/'
#define MAX_BUFFER 65529
#define MAX_COMMAND_LEN 6
#define SPACE ' ' || '\t'
#define eq_int(A,B) (A==B)
#define eq_char(A,B) !(strcmp(A,B))


enum commands {HELP, QUIT, SET, PRINT, FIND, LIST, SEARCH, DELETE, NONE};

int main() {
    /* NUNCA PERDER ESTA ROOT */
    tree_node_s root = treeConstructor();
    stack_s stack = NULL;
    char buffer[MAX_BUFFER];
    int quit=0;
    int command;

    while (!quit) {

        command = aux(buffer);

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
                treeDestructor(root);
                clear(buffer);
                quit = 1;
                break;
            
            case SET:              
                treeAdd(root, buffer);
                break;
            
            case PRINT:
                treePrint(root, stack);
                break;

            case FIND:
                treeFind(root, buffer);
                break;

            case LIST:
                treeList(root, buffer);
                break;

            case SEARCH:
                treeSearch(root, buffer, stack);
                break;
            
            case DELETE:
                treeDelete(root, buffer);
                break;            
        }
    }      

    return 0;
}

int aux(char buffer[]) {

    char command[MAX_COMMAND_LEN+1];
    char c;
    int i=0, j=0, counter=0;
    int readCommand = 0, reading = 1;;

    clear(buffer);

    while((c=getchar()) != EOF && c != '\n') {
        if (counter == 65535) {
            strcpy(command, "quit");
            printf("no memory\n");
            break;
        }
        counter++;

        if (c == ' '  && !readCommand) {
            readCommand = 1;
            reading = 0;
        }
        else if (c != ' ' && reading) {
            command[i++] = c;
        }
        else{
            buffer[j++] = c;
        }
    }
    command[i] = '\0';
    buffer[j] = '\0';  

    if (eq_char(command, "help")) {
        clear(command);
        return HELP;        
    }
    else if (eq_char(command, "quit")) {
        clear(command);
        clear(buffer);
        return QUIT;
    }
    else if (eq_char(command, "set")) {
        clear(command);
        return SET;
    }
    else if (eq_char(command, "print")) {
        clear(command);
        return PRINT;
    }
    else if (eq_char(command, "find")) {
        clear(command);
        return FIND;
    }
    else if (eq_char(command, "list")) {
        clear(command);
        return LIST;
    }
    else if (eq_char(command, "search")) {
        clear(command);
        return SEARCH;
    }
    else if (eq_char(command, "delete")) {
        clear(command);
        return DELETE;
    }
    return QUIT;
}



void clear(char string[]) {
    int i;
    i = strlen(string);
    memset(string, '\0', i);
}

void printTest(tree_node_s root) {
    tree_node_s child = root->child;
    printf("[printTest] %s\n", child->path);
    printf("\n");
    while (child != NULL) {
        printf("child : %s, ", child->path);
        child = child->brother;
    }
    
    printf("\n");
}
