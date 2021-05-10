#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define eq_int(A,B) (A==B)
#define eq_char(A,B) !(strcmp(A,B))
#define MAX_BUFFER 200
#define MAX_COMMAND_LEN 6
#define SPACE ' ' || '\t'

typedef struct input{
    char *command;
    char *path;
    char *value;
} *input_s;

input_s constructor_i(){

    input_s new_input = (input_s)malloc(sizeof(input_s));

    new_input->command=NULL;
    new_input->path=NULL;
    new_input->value=NULL;

    return new_input;
}

void destructor_i(input_s input) {
    free(input->command);
    if (input->path != NULL) {
        free(input->path);
    }
    if (input->value != NULL) {
        free(input->value);
    }
    free(input);
}

char *read_line() {
    char c;
    char *buffer;
    char temp[MAX_BUFFER+1];
    int i=0;
    while ((c=getchar()) != EOF && c!= '\n') {
        temp[i++] = c;
    }
    temp[i] = '\0';
    buffer = (char *)malloc(sizeof(char)*i);
    strcpy(buffer, temp);
    return buffer;
}

char *read_command(char *buffer) {
    
    int i=0, j;
    char c;
    char command_temp[MAX_COMMAND_LEN+1];
    char buffer_temp[MAX_BUFFER-(MAX_COMMAND_LEN+1)];
    char *command;
    char *copy_buffer = buffer; 


    while (*(copy_buffer) != ' '){
        command_temp[i++] = *(copy_buffer++);
    }

    command_temp[i] = '\0';
    
    for (i=i-1, j=0; (c=copy_buffer[i]) != '\0'; i++){
        buffer_temp[j++] = c;     
    } 
    buffer_temp[j] = '\0';
    
    command = (char *)malloc(sizeof(char)*(i));
    strcpy(command, command_temp);
    buffer = (char *)realloc(buffer, sizeof(char)*(strlen(buffer_temp)+1));
    strcpy(buffer, buffer_temp);    

    return command;
}



int main() {
    char *buffer;
    char *command;
    
    /* criar o novo input */

    input_s *new_input = constructor_i(); 

    /* ler o comando pedido*/ 

    buffer = read_line();
    command = read_command(buffer);


    
    

    return 0;
}










