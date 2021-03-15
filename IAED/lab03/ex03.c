#include <stdio.h>


void cruz(int n) {

      int lc;

    /* pair num */
    if (n%2 == 0) {
        for (lc=1; lc < 5; ++lc) {
            if (lc == 1) {
                printf("* - - -\n");
            }
            else if (lc == 2) {
                printf("- * - -\n");
            }
            else if (lc == 3) {
                printf("- - * -\n");
            }
            else {
                printf("- - - *\n");
            }
        }

        for (lc=1; lc < 5; ++lc) {
            if (lc == 1) {
                printf("* - - -\n");
            }
            else if (lc == 2) {
                printf("- * - -\n");
            }
            else if (lc == 3) {
                printf("- - * -\n");
            }
            else {
                printf("- - - *\n");
            }
        }
    }

    /* impair num */
    else {


    }


}

int main() {

    int n;

    printf("?\n");
    scanf("%d", &n);

    cruz(n);

    return 0;
}