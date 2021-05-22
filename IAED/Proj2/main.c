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
    char buffer[MAX_PATH+1], value[MAX_PATH], *array;
    int quit=0;
    int command, size;

    while (!quit) {

        command = switchForCommand(buffer);          

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
                clear(buffer);
                free(extremes);
                free(head);
                free(root);
                quit = 1;
                break;
            
            case SET:    
                treeAdd(root, buffer);
                clear(buffer);
                break;
            
            case PRINT:
                treePrint(root, extremes, head, buffer);
                clear(buffer);
                break;

            case FIND:
                treeFind(root, buffer);
                clear(buffer);
                break;

            case LIST:
                treeList(root, buffer);
                clear(buffer);
                break;

            case SEARCH:
                    clear(value);
                    array = strtok(buffer, " ");                
                    while( array != NULL ) {     
                        strcat(value, array);   
                        strcat(value, " ");
                        array = strtok(NULL, " ");
                    }                   
                    size = strlen(value)-1;   
                    value[size] = '\0'; 
                
                treeSearch2(root, extremes, head, value);                
                clear(buffer);
                break;
            
            case DELETE:
                treeDelete(root, buffer);
                clear(buffer);
                break;            
        }
    }      

    return 0;
}

int switchForCommand(char buffer[]) {   

    char *command, *array;
    char aux[MAX_PATH+1];      

    readLine(buffer); 
    strcpy(aux, buffer);  

    command = strtok(aux, " ");

    array = strtok(NULL, "\0");

    if (array!=NULL) strcpy(buffer, array);
    else buffer[0] = '\0';

    if (strcompare(command, "help")) {
        clear(command);
        return HELP;        
    }
    else if (strcompare(command, "quit")) {
        clear(command);
        return QUIT;
    }
    else if (strcompare(command, "set")) {
        clear(command);
        return SET;
    }
    else if (strcompare(command, "print")) {
        clear(command);
        return PRINT;
    }
    else if (strcompare(command, "find")) {
        clear(command);
        return FIND;
    }
    else if (strcompare(command, "list")) {
        clear(command);        
        return LIST;
        
    }
    else if (strcompare(command, "search")) {
        clear(command);
        return SEARCH;
    }
    else if (strcompare(command, "delete")) {
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

void readLine(char buffer[]) {
    char c;
    int i=0;

    while ((c=getchar())!= '\n' && c != EOF) {
            buffer[i++] = c; 
    }
    buffer[i] = '\0';

    return;

}

int strcompare(char str1[], char str2[]) {
    int i;

    /*printf("str1: |%s|\nstr2: |%s|\n", str1, str2);*/

    if (str1[0] == '\0' || str2[0] == '\0') {
        /*printf("not equals!\n\n");*/
        return 0;
    }

    for(i=0; str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i]!= str2[i]) {
            /*printf("not equals!\n\n");*/
            return 0;
        }
    }
    if (str1[i] != str2[i]) {
        /*printf("not equals!\n\n");*/
        return 0;
    }
    /*printf("equals!\n\n");*/
    return 1;
}