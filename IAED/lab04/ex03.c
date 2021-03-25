#include <stdio.h>
#define VECMAX 100

void VertGraphGrow(int n) {
    
    int tab[VECMAX];
    /* col num = n */
    int col, line, bignum = 0, i;
    
    for (i=0; i < n; i++) {
        printf("?\n");
        scanf("%d", &tab[i]);
        if (tab[i] > bignum) {
            bignum = tab[i];
        }
    }

    for (line = 0; line < bignum; line ++) {
        for (col = 0; col < n; col ++) {
            if (tab[col] - (n - line + 1) >= 0) {
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
    
    int n;
    
    printf("?");
    scanf("%d", &n);
    
    if (n > 100) {
        printf("inserir n < 100 ?");
        scanf("%d", &n);
    }
    
    VertGraphGrow(n);
    
    return 0;
}
