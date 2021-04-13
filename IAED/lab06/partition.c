#include <stdio.h>

void exch(int sort[], int i, int j) {
	int temp;
	temp = sort[i];
	sort[i] = sort[j];
	sort[j] = temp;
}


int less(int v, int a_j) {

	if (v < a_j) {
		return 1;
	}	
	return 0;
}


int partition(int sort[], int l, int r) {

	int i = l-1; 
	int j = r; 
	int v = sort[r]; /* pivo */
	while (i < j) { /* enquanto o iterador da esquerda for menor do que o da direita */
		while (less(sort[++i], v)); /* procura elemento maior que o pivot -> */
		while (less(v, sort[--j])) /* procura elemento menor que o pivot <- */
			if (j == l) /* para quando o elemento da particao esta na primeira posicao */
				break;
		if (i < j)
			exch(sort, i, j); /* troca se o maior para a posicao do menor e vice versa */
	}
	
	exch(sort, r, i); /* no fim de tudo, troca o pivo (a[r]) com o numero do meio (a[j])  */

	return i; /* retorna o ponto onde partiu o vetor, ou seja, o meio */
}

int main() {

    int i, res;

    int sort[11];
    for (i=0; i<11; i++) {
        scanf("%d", &sort[i]);
    }

    res = partition(sort, 0, 10);

    printf("pivo = %d\n",res);

    for (i=0; i<11; i++) {
        printf("%d ", sort[i]);
    }
    
    printf("\n");

    return 0;
}