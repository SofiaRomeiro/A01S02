#include <stdio.h>

int main() {

    int i;
    char c, n;

    for (i=0; i < 100; i++) {
        c = getchar();
        if (c >= '0' && c <= '9') {
            n += (c - '0');
        }     
    }
    printf("%s\n", n % 9 == 0 ? "yes" : "no");    
    return 0;
}