#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"



int main() {
    /* NUNCA PERDER ESTA ROOT */
    tree_node_s root = treeConstructor();
    list_ext_s extremes = (list_ext_s) malloc(sizeof(struct listExtremes));
    list_node_s head = (list_node_s) malloc(sizeof(struct list_node));
    char buffer[MAX_PATH+1];
    int quit=0;
    int command, args;

    while (!quit) {

        command = switchForCommand();               

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
                treeDelete(root);
                clear(buffer);
                free(extremes);
                free(head);
                free(root);
                quit = 1;
                break;
            
            case SET:      
                treeAdd(root);
                clear(buffer);
                break;
            
            case PRINT:
                treePrint(root, extremes, head);
                clear(buffer);
                break;

            case FIND:
                treeFind(root);
                clear(buffer);
                break;

            case LIST:
                args = 1;
                treeList(root, args);
                clear(buffer);
                break;

            case LISTNOARG:
                args=0;
                treeList(root, args);
                clear(buffer);
                break;

            case SEARCH:
                readValue(buffer);
                treeSearch(root, buffer, extremes, head);                
                clear(buffer);
                break;
            
            case DELETE:
                treeDelete(root);
                clear(buffer);
                break;            
        }
    }      

    return 0;
}

int switchForCommand() {   

    char command[MAX_COMMAND_LEN], c;
    int i=0, no_args=0;   

    while ((c=getchar())!= ' ' && c != EOF) {
        command[i++] = c;
        if (c=='\n') {
            no_args=1;
            command[i-1] = '\0'; 
            break;
        }
    }
    command[i] = '\0';

    if (equals(command, "help"))) {
        clear(command);
        return HELP;        
    }
    else if (equals(command, "quit"))) {
        clear(command);
        return QUIT;
    }
    else if (equals(command, "set"))) {
        clear(command);
        return SET;
    }
    else if (equals(command, "print"))) {
        clear(command);
        return PRINT;
    }
    else if (equals(command, "find"))) {
        clear(command);
        return FIND;
    }
    else if (equals(command, "list"))) {
        clear(command);
        if (no_args) {
            printf("aaa\n");
            return LISTNOARG;
        }
        else {
            return LIST;
        }
        
    }
    else if (equals(command, "search"))) {
        clear(command);
        return SEARCH;
    }
    else if (equals(command, "delete"))) {
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

void readValue(char buffer[]) {
    char *array,c, read[MAX_PATH];
    int size, i=0;

    while((c=getchar())!=EOF && c != '\n') {
        read[i++]=c;
    }
    read[i] = '\0';

    array = strtok(read, " ");
   
    while( array != NULL ) {     
        strcat(buffer, array);   
        strcat(buffer, " ");
        array = strtok(NULL, " ");
    }

    

    size = strlen(buffer)-1;
    buffer[size] = '\0';

    printf("[readValue]buffer? %s\n", buffer);

    return;

}