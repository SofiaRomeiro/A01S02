#include <stdio.h>

void distcount(int a[], int l, int r){
    
    int i, j, cnt[M+1];
    int b[maxN];
    for (j = 0; j <= M; j++)
        cnt[j] = 0;
    for (i = l; i <= r; i++)
        cnt[a[i]+1]++;
    for (j = 1; j < M; j++)
        cnt[j] += cnt[j-1];
    for (i = l; i <= r; i++)
        b[cnt[a[i]]++] = a[i];
    for (i = l; i <= r; i++)
        a[i] = b[i];
}

void distcount2(int a[], int l, int r) {
    int i, j, cnt[M];
    int b[maxN];
    for (j = 0; j < M; j++)
        cnt[j] = 0;
    for (i = l; i <= r; i++)
        cnt[a[i]]++;
    for (j = 1; j < M; j++)
        cnt[j] += cnt[j-1];
    for (i = r; i >= l; i--)
        b[--cnt[a[i]]] = a[i];
    for (i = l; i <= r; i++)
        a[i] = b[i];
}