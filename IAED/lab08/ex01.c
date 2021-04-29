#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {

    int i=0;
    char *phrase = malloc(10001);

    scanf("%s", phrase);

    while (phrase[i]) {
        printf("%s\n", phrase);
        phrase++;
    }
    return 0;
}