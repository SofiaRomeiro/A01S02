#include <stdio.h>

typedef struct complex {
    int real;
    int imag;
} complex;

complex sumComplex(complex a, complex b, complex sum) {

    sum.real = a.real + b.real;
    sum.imag = a.imag + b.imag;
    
    return sum;
}

int main() {
    complex a;
    complex b;
    complex sum;
    
    int i, real=0;
    char c;

    a.real=0;
    a.imag=0;
    b.real=0;
    b.imag=0;
    sum.real=0;
    sum.imag=0;   

   
    printf("numero ?\n");
    for (i=0; (c = getchar()) != EOF && c != '\n'; i++) {
        
        if (!real && c >= '1' && c <='9') {
            a.real = a.real * 10 + (c-'0');
        }
        else if (c == '+' && !real) {
            real = 1;
        }
        else if (real && c >= '1' && c <='9') {
            a.imag = a.imag * 10 + (c-'0');
        }
    }

    real = 0;
    printf("numero ?\n");
    for (i=0; (c = getchar()) != EOF && c != '\n'; i++) {
        if (!real && c >= '1' && c <='9') {
            b.real = b.real * 10 + (c-'0');
        }
        else if (c == '+' && !real) {
            real = 1;
        }
        else if (real && c >= '1' && c <='9') {
            b.imag = b.imag * 10 + (c-'0');
        }
    }

    sum = sumComplex(a,b,sum);

    printf("%d+%di", sum.real, sum.imag);

    return 0;
}