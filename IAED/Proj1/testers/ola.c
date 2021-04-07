#include <string.h>
#include <stdio.h>


void escreve(char a[], int command) {
    int i;

    if (command) {

        for (i=0; i <10; i++) {
            a[i] = 'a';
        }
        a[i] = '\0';
    }
    else {
        for (i=0; i <10; i++) {
            a[i] = 'b';
        }
        a[i] = '\0';
    }
}

int main() {

    char a[10];
    char b[10];
    char c[10];

    escreve(a,1);
    strcpy(b, a);
    printf("%s\n", b);

    escreve(c, 0);
    strcpy(b, c);
    printf("%s\n", b);

    return 0;
}
