#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 1000

int main() {

    int count=0, i;
    char buffer[MAX_WORD_LEN];
    char **word_list=0;

    while (scanf("%s", buffer)==1) {

        word_list=realloc(word_list, sizeof(char *)*(count + 1));
        word_list[count] = malloc(sizeof(char) * (strlen(buffer)+1));
        strcpy(word_list[count], buffer);
        count++;
    }

    for (i=count-1; i >= 0; --i) {
        printf("%s\n", word_list[i]);
        free(word_list[i]);
    }
    free(word_list);
    return 0;
}