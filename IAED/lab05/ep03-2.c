#include <stdio.h>

#define MAXPAISES 200
#define MAXCIDADE 500
#define MAXNOME 50

Pais onu[MAXPAISES];

typedef struct Cidade {
    char nome[MAXNOME];
    int populacao;
    double latitude;
    double longitude;
} Cidade;

typedef struct Pais {
    char nome[MAXNOME];
    int cidades;
    Cidade cidadesl[MAXCIDADE];
} Pais;

void pais(Pais p[], int max) {

    int maxpop, i, j, country;

    maxpop = p[0].cidades[0].pop;

    for (i=0; i < max; i++) {
        for (j=0; j < p[i].cidades; j++) {
            if (p[i].cidadesl[j].pop > maxpop) {
                maxpop = p[i].cidadesl[j].pop;
                country = i;
            }
        }
    }
    printf("%s\n", p[i].nome);
}

int main() {
    return 0;
}