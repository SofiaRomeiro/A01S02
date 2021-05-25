#include <string.h>
#include <stdio.h>

typedef struct frase {
    char frase[20];
} frase_t;

int j=0;
int n=0;
frase_t frases[5];


void desempata(int temporary_i[], int contador_iguais, int correct_order[]) {

    int res;
    res = strcmp(frases[temporary_i[1]].frase, frases[temporary_i[0]].frase);       
    
    if (res<0) {
        correct_order[0] = temporary_i[1];
        correct_order[1] = temporary_i[0];
    }
    else {
        correct_order[0] = temporary_i[0];
        correct_order[1] = temporary_i[1];
    }
}

void alfabeticOrder() {

    char chr = 'a';
    int temporary_i[5];
    int ordem[5];
    int correct_order[5];

    while (chr <= 'z') {

        int contador_iguais=0;       

        for (j=0; j < 5; j++) {
            if (frases[j].frase[0] == chr) {
                temporary_i[contador_iguais++] = j;       
            }
        }  

        if (contador_iguais==1) {
            ordem[n++] = temporary_i[0];        
        }
        
        else if (contador_iguais>1) {
            
            desempata( temporary_i, contador_iguais, correct_order);  
            for (j=0; j < contador_iguais; j++) {
                ordem[n++] = correct_order[j];

            }  
        }

    chr = chr + 1; 
}

    for (j=0; j < n; j++) {
        printf("%s\n", frases[ordem[j]].frase); 
    }  
}


int main() {
   
    strcpy(frases[0].frase, "sou um bolo");
    strcpy(frases[1].frase, "gosto de banana");
    strcpy(frases[2].frase, "o vasco e lindo");
    strcpy(frases[3].frase, "sou linda");
    strcpy(frases[4].frase, "hoje choveu");  


/* procurar por chars (maiusculas ou minusculas) */

    alfabeticOrder();

    return 0;
}
