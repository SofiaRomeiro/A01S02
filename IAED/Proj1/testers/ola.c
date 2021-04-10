#include <string.h>
#include <stdio.h>

typedef struct frase {
    char frase[20];
} frase_t;


int main() {

    frase_t frases[5];
    char chr = 'a';
    int i = 'a', j, k=0, len=0;
    int ordem[5];

    strcpy(frases[0].frase, "sou um bolo");
    strcpy(frases[1].frase, "gosto de banana");
    strcpy(frases[2].frase, "o vasco e lindo");
    strcpy(frases[3].frase, "sou linda");
    strcpy(frases[4].frase, "hoje choveu");  

    for (i=0; i<5; i++) {
        if (strlen(frases[0].frase) > len) {
            len = strlen(frases[0].frase);
            printf("%d\n", len);
        }
    }

    while (chr <= 'z') {
        for (i=0; i < 5; i++) {
            if ((frases[i].frase[0] == chr) || (frases[i].frase[0] == chr - ('a'-'A'))) {
                ordem[k++] = i;
                printf("%d\n", i);
            }
        }
        chr = chr + 1;
    }
    

    printf("%s\n%s\n%s\n%s\n%s\n", frases[ordem[0]].frase, frases[ordem[1]].frase, frases[ordem[2]].frase, frases[ordem[3]].frase, frases[ordem[4]].frase);

    return 0;
}
