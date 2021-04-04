#include <string.h>
#include <stdio.h>

int main() {
    int i, res;
    char str1[4+1];
    char str2[4+1];

    for (i=0; i < 4; i++) {
        str1[i] = 'a';       
    }
   
    str1[i]='\0';

    for (i=0; i < 4; i++) {
        str2[i] = 'a';       
    }
   
    str2[i]='\0';

    printf("%s\n%s\n", str1, str2);    

    res = strcmp(str1, str2);

    printf("%d\n", res);

    return 0;
}


