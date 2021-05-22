#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strcompare(char str1[], char str2[]) {
    int i;

    if (str1[0] == '\0' || str2[0] == '\0') {
        return 0;
    }

    for(i=0; str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i]!= str2[i]) {
            return 0;
        }
    }
    if (str1[i] != str2[i]) {
        return 0;
    }
    return 1;
}

int main() {

    char str1[200], str2[200], c;
    int compare, i=0;

    while ((c=getchar()) != EOF && c != '\n') {
        str1[i++] = c;
    }
    str1[i] = '\0';

    i=0;
    while ((c=getchar()) != EOF && c != '\n') {
        str2[i++] = c;
    }
    str2[i] = '\0';


    printf("|%s|\n|%s|\n", str1, str2);

    compare= strcompare(str1, str2);

    printf(!compare ? "NO!" : "YES!!");

    return 0;
}