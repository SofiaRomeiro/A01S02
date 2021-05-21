#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *array;
    char pila[200];
    int found = 0, j=0;
    char c, directory[200], value[200];

    scanf("%s", directory);
    printf("path: |%s|\n", directory);

    array = strtok(directory, "/");

    while( array != NULL ) {
        printf("array: %s\n", array); 

        array = strtok(NULL, "/");
    }

    return 0;
}

void ola() {
    char c, directory[100], value[100];
    int found=0, j=0;

     while((c=getchar())!= EOF && c != '\n') {

        printf("char: %c\n", c);
       
       /* se for igual a espaço/tab e ainda nao tiver começado a ler, continuo */
       if ((c==' ') && !found) {
           continue;
       }

       /* se for igual a uma barra, vejo se o diretorio nao é vazio e adiciono novo node */
       else if (c == '/') {
           if (!strcmp(directory, "")) {
               memset(directory,'\0',strlen(directory));
               j=0;
           }
           else {
               /* adicionar node */
               memset(directory,'\0',strlen(directory));
               j=0;
           }
       }
       /* se for diferente de espaço/tab e diferente de barra,adiciono ao diretorio */
       else if (c != ' ' && c != '\t') {
           found = 1;
           directory[j++] = c;
       }
       else if (c == ' ' && found){
           if (strcmp(directory, "")) {
               /* adicionar node */
               j=0;
           }  
           else {
               continue;
           }                    
       }
       else {
         
       }
    } 

    while ((c=getchar()) != EOF  && c != '\n') {
        if (c == ' ' && !found) { 
        }  
        else {
            found = 1;
            value[j++] = c;         
        }
    }
    value[j] = '\0';
}