#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

struct input{
    char *command;
    char *path;
    char *value;
};

input_s inputConstructor(){

    input_s new_input = (input_s) malloc(sizeof(input_s));

    new_input->command=NULL;
    new_input->path=NULL;
    new_input->value=NULL;

    return new_input;
}

void inputDestructor(input_s input) {
    free(input->command);
    if (input->path != NULL) {
        free(input->path);
    }
    if (input->value != NULL) {
        free(input->value);
    }
    free(input);
}