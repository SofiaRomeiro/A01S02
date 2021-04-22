#include <stdio.h>

#define bitsword 24
#define bitsbyte 8
#define bytesword 3
#define digit(a,b) a[b]
#define R (1 << bitsbyte)
#define digit(n,w) ((n & ( 1 << w )) >> w) 
#define bin(A) l+count[A]

void radixMSD(Item a[], int l, int r, int w) {
    int i, j, count[R+1];
    if (w > bytesword)
        return;
    if (r-l <= M) {
        insertion(a, l, r);
    return;
    }
    for (j = 0; j < R; j++)
        count[j] = 0;
    for (i = l; i <= r; i++)
        count[digit(a[i], w) + 1]++;
    for (j = 1; j < R; j++)
        count[j] += count[j-1];
    for (i = l; i <= r; i++)
        aux[l+count[digit(a[i], w)]++] = a[i];
    for (i = l; i <= r; i++)
        a[i] = aux[i];

    radixMSD(a, l, bin(0)-1, w+1);

    for (j = 0; j < R-1; j++)
        radixMSD(a, bin(j), bin(j+1)-1, w+1);
}






