#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"
#define MAX_PATH

int main() {

    // len 11

    char teste[30];
    strcpy(teste, "ola bom dia");

    printf("%d\n", strlen(teste));

    return 0;
}