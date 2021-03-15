#include <stdio.h>


void cruz(int n) {

      int line, pos;

    /* pair num */
    if (n%2 == 0) {
        for (line=1; line < 9; ++line) {

            for (pos=1; pos < 9; ++pos) {

                printf("\n%d -> pos\n", pos);


                if (pos==line || (pos == (n-line) + 1)) {
                    if (pos != 8) {
                        printf(" * ");
                    }
                    else {
                        printf(" * \n");
                    }
                    
                }
                else {
                    if (pos != 8) {
                        printf(" - ");
                    }
                    else {
                        printf(" - \n");
                    }
                    
                }
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