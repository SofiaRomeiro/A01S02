#include <stdio.h>
#include <string.h>

#define TOPIC 30
#define MAXISBN 13
#define AUTHORS 10
#define NAME 100
#define MAXESTANTE 20
#define MAXBOOKS 10000 

typedef struct Livro {
    char ISBN[MAXISBN+1];
    char authors[AUTHORS][NAME+1];
    int edition_number;
    int number_copies;
    float price;
} Livro;

typedef struct Estante {
    int number;
    char topic[TOPIC+1];
    int shelf;
    Livro booklist[MAXBOOKS];
} Estante;

typedef struct Livraria {
    Estante list[MAXESTANTE];
} Livraria;

int vendeLivro(Livro l[], int n, char isbn[], int k) {

    int i;

    for (i=0; i < n; i++) {
        if (!(strcmp(isbn, l[i].ISBN))) {
            if (l[i].number_copies >= k) {
                l[i].number_copies -= k;
            }
            else {
                printf("COPIASINSUFICIENTES");
            }
        }
        else {
            printf("NAOEXISTE");
        }
    }

    return 1[i].number_copies;
}


int main() {

    Livro l[MAXBOOKS];
    int n = MAXBOOKS;
    char isbn[MAXISBN+1];
    int k = 10;

    vendeLivro(l, n, isbn, k);

    return 0;
}


