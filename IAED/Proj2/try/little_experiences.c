#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    
    char *name = NULL;
    char *message = NULL; 

    char number[10];
    char buffer_message[1000];
    char buffer_name[1000];
    char c;
    int r_name=0, r_number=0, r_message=0;
    int i=0, j=0, k=0;

    while((c=getchar()) != EOF && c != '\n') {

        if (c != ' ' && !r_number) {
            number[i++] = c;
        }

        else if (c == ' ' && !r_number) {
            number[i]='\0';
            r_number = 1;
        }

        else if (c == ' ' && !r_message) {
            continue;
        }
        
        else if (c != ' ' && !r_name) {            
            buffer_name[j++] = c;
        }

        else if (c == ' ' && !r_name) {
            r_name = 1;
        }

        else {
            r_message=1;
            buffer_message[k++] = c;
        }
    }
    
    buffer_name[j] = '\0';
    buffer_message[k] = '\0';  

      
    if (buffer_name[0] != '\0') {
        name = (char *)malloc(sizeof(char)*(strlen(buffer_name)+1));
        strcpy(name, buffer_name);
    }

    if (buffer_message[0] != '\0') {
        message = (char *)malloc(sizeof(char)*(strlen(buffer_message)+1));
        strcpy(message, buffer_message);
    }

    printf("%s, %s, %s\n", number, name, message);





    

    
    return 0;
}