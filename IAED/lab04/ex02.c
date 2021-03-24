#include <stdio.h>
#define VECMAX 100


void VertGraphSus(int n) {

    int biggest = 0, i, c, l;
    int tab[VECMAX];

    for (i=0; i < n; i++) {
        printf("?\n");
        scanf("%d", &tab[i]);
        if (tab[i] > biggest) {
            biggest = tab[i];
        }
    }

    for (c = 0; c < biggest; c++) {
        for (l = 0; l < n; l++) {
            if ((tab[l] - c) > 0) {
                printf("*");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main() {

    int n = 0;   

    printf(" valor de n menor que 100?\n");
    scanf("%d", &n);

    if (n > 100) {
        printf(" valor de n menor que 100?\n");
        scanf("%d", &n);
    }    

    VertGraphSus(n);

    return 0;
}