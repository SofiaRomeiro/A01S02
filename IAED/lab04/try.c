#include <stdio.h>
#define TRY 3

int main () {
    char tab[TRY];
    int i;

    tab[0] = 1;
    tab[1] = 2;
    tab[2] = 3;

    for (i=0; i < TRY; i++) {
        printf("%d", tab[i]);
    }
    return 0;
}