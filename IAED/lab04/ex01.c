#include <stdio.h>

#define VECMAX 100

int main() {
    int n = 0, i, j;
    int tab[VECMAX];    

    printf(" valor de n menor que 100?\n");
    scanf("%d", &n);

    if (n > 100) {
        printf(" valor de n menor que 100?\n");
        scanf("%d", &n);
    }    

    for (i=0; i < n; i++) {
        printf("?");
        scanf("%d", &tab[i]);
    }

    for (i=0; i < n; i++) {
        for (j=1; j < tab[i]; j++)
            printf("*");
        printf("*\n");
    }

    return 0;
}