#include <stdio.h>

void piramide(int n) {

    int line, i;
    /*number of lines are always equal to n*/

    
    if (n > 1) {
       
        for (line = 1; line < n + 1; line++) {             
            /* first blank spaces */
            for (i = 1; i <= (n - line); i++) {
                printf("  ");
            }
            
            /* crescent elements */
            for (i = 1; i < (line + 1); i++) {         
                printf("%d ", i);
            }

            /* decrescent elements */
            for (i = line - 1; i > 0; i--) {
                printf("%d ", i);
            }

            /* last blank spaces */
            for (i = 1; i <= (n - line); i++) {
                printf("  ");
            }

            printf("\n"); 
        }

    } 
    else {
        printf("O numero tem de ser igual ou superior a 2\n");
    }

}

int main() {

    int n;

    printf("?");
    scanf("%d", &n);

    piramide(n);

    return 0;
}