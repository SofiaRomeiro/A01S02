#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"

#define ROOT '/'
#define MAX_BUFFER 65534
#define MAX_COMMAND_LEN 6
#define SPACE ' ' || '\t'
#define eq_int(A,B) (A==B)
#define equals(A,B) !(strcmp(A,B))


enum commands {HELP, QUIT, SET, PRINT, FIND, LIST, SEARCH, DELETE, NONE};

int main() {
    /* NUNCA PERDER ESTA ROOT */
    tree_node_s root = treeConstructor();
    stack_s stack = NULL;
    char buffer[MAX_BUFFER+1];    
    int quit=0;
    int command;
    buffer[0] = '\0';

    while (!quit) {

        memset(buffer, '\0', MAX_BUFFER+1);
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
                treeDelete(root, buffer);
                free(root->path);
                free(root);
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

    char *command, *array;
    char aux[MAX_BUFFER+1];      

    readLine(buffer); 

    /* se tiver escrito no memory, é porque a memoria foi excedida e deve terminar */
    if (equals(buffer, "No memory.")) {
        return QUIT;
    }

    strcpy(aux, buffer);  

    command = strtok(aux, " \t");
    array = strtok(NULL, "\0");

    if (array!=NULL) strcpy(buffer, array);
    else buffer[0] = '\0';


    if (!hashing(command, "help")) {
        clear(command);
        return HELP;        
    }
    else if (!hashing(command, "quit")) {
        clear(command);
        clear(buffer);
        return QUIT;
    }
    else if (!hashing(command, "set")) {
        clear(command);
        return SET;
    }
    else if (!hashing(command, "print")) {
        clear(command);
        return PRINT;
    }
    else if (!hashing(command, "find")) {
        clear(command);
        return FIND;
    }
    else if (!hashing(command, "list")) {
        clear(command);
        return LIST;
    }
    else if (!hashing(command, "search")) {
        clear(command);
        return SEARCH;
    }
    else if (!hashing(command, "delete")) {
        clear(command);
        return DELETE;
    }
    return QUIT;
}

void readLine(char buffer[]) {
    char c;
    int i=0;

    while ((c=getchar())!= '\n' && c != EOF) {
        if (i == MAX_BUFFER+2) {
            printf("No memory.\n");
            strcpy(buffer, "No memory.");
            return;            
        }
        buffer[i++] = c;             
    }
    buffer[i] = '\0';

    return;

}

int hashing(char a[], char b[]) {
    if (a[0] != b[0])
        return 1;
    else
        return strcmp(a, b);
}


void clear(char string[]) {
    string[0] = '\0';
}

void filter(char buffer[]) {
    int i = strlen(buffer)-1;
    for(; i > 0; i--) {
        if (buffer[i] == ' ' || buffer[i] == '\t') {
            buffer[i] = '\0';
        }
        else if (buffer[i] != ' ' && buffer[i] != '\t'){
            return;
        }
    }
}
