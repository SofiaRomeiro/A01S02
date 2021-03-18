#include <stdio.h>

int main() {

    int n=0;
    char c;
    char op[5];
      
    while ((c = getchar()) != '\n') {
        if (c >= '0' && c <= '9') {
            printf("%c -> c \n", c);
            n = n*10 + (c - '0');
            printf("%d -> n\n", n);
        }

        else if (c == '+') {
            op = "sum";
        }
        else if (c = '-') {
            op = "sub";
        }
        
    }

    printf("%d", n);
    return 0;

}