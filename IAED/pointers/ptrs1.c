#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int modulo(int a) { return a < 0 ? -a : a; }
int dobro(int a) { return a*2; }

void escreve(int (*func)(int), int valor){
    printf("%d\n",(*func)(valor));
}

int main() {
    char *s;
    s = (char *)malloc(sizeof(char)*5);
    memset(s, 'A', 5*sizeof(char));    
    printf("%s\n", s);
}



