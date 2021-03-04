#include <stdio.h>

int main() {

    float fahr, celsius;
    int inferior, superior, passo;

    inferior = 0;
    superior = 300;
    passo = 20;

    fahr = inferior;

    while (fahr <= superior)
    {
        celsius =  5 * (fahr - 32) / 9.0;
        /* celsius = (5.0 / 9.0) * (fahr - 32); */
        printf("%3f\t%6f\n, fahr, celsius") 
        /* o numero depois do % e antes do d (decimal) significa o n de espacos gastos para imprimir */
        fahr += passo
    }

    for (fahr = inferior, fahr <= superior, fahr += passo)
    {
        celsius = (5.0 / 9.0) * (fahr - 32);
        printf("%3f\t%6f\n, fahr, celsius")
    }
}

/* ma pratica utilizar valores explicitos --> usar constantes com #define */