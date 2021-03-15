#include <stdio.h>

void quadrado(int n) {

    int i, j;

    if (n >= 2) {
        for (i = 1; i <= n; i++) {
            for (j = 0; j < n - 1; j++) {
                printf("%d\t", i + j);
            }
            printf("%d\n", i + j);
        }     
    }
    else {
        printf("O numero tem de ser igual ou superior a 2\n");
    }
}

int main() {

    int n;

    printf("?\n");
    scanf("%d", &n);

    quadrado(n);

    return 0;
}