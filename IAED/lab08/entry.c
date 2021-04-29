#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *name;
    int len;
    double *val;
} Reals; 

Reals *reals(FILE *in, int *size) {

    char buffer[255];

    FILE* fp = fopen("ola.txt","r");

    fgets(buffer,255,fp);

    printf("%s\n", buffer);

    fclose(fp);

    return NULL;
}

int main() {
    reals(NULL, NULL);
    return 0;
}