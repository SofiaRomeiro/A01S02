#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct frase {
	char frase[20]; 
	int id;
} frase_t;

frase_t frases[10];


void exch(frase_t sort[], int i, int j) {
	frase_t temp;
	temp = sort[i];
	sort[i] = sort[j];
	sort[j] = temp;
}


int less(frase_t sort[], int v, int a_j, int x, int y) {

	int res;

	if (v < a_j) {
		return 1;
	}	
	else if( v == a_j) {
		res = strcmp(sort[x].frase, sort[y].frase);
		if (res < 0) {
			return 1;
		}
	}
	return 0;
}


int partition(frase_t sort[], int l, int r) {

	int i = l-1; 
	int j = r; 
	int v = sort[r].id; /* pivo */
	while (i < j) { /* enquanto o iterador da esquerda for menor do que o da direita */
		while (less(sort, sort[++i].id, v, i, r)); /* procura elemento maior que o pivot -> */
		while (less(sort, v, sort[--j].id, r, i)) /* procura elemento menor que o pivot <- */
			if (j == l) /* para quando o elemento da particao esta na primeira posicao */
				break;
		if (i < j)
			exch(sort, i, j); /* troca se o maior para a posicao do menor e vice versa */
	}
	
	exch(sort, r, i); /* no fim de tudo, troca o pivo (a[r]) com o numero do meio (a[j])  */

	return i; /* retorna o ponto onde partiu o vetor, ou seja, o meio */
}

void quicksort(frase_t sort[], int l, int r) {
	int i;

	if (r <= l)
		return;

	i = partition(sort, l, r);
	quicksort(sort, l, i-1);
	quicksort(sort, i+1, r);
}



int main() {

	int i, max=9;
	frase_t sort[10];
	frase_t frases[10];


/*	for (i=0; i <= max; i++) {
		nums[i] = (int) 100 *(1.0* rand() / RAND_MAX);
		if (i < max) {
			printf("%d ", nums[i]);
		}
		else {
			printf("%d\n", nums[i]);
		}
	} */	

	strcpy(frases[0].frase, "gosto de pao");
	frases[0].id = 5;	
	strcpy(frases[1].frase, "o ceu e azul");
	frases[1].id = 2;
	strcpy(frases[2].frase, "canecas rosa");
	frases[2].id = 1;
	strcpy(frases[3].frase, "minions amarelos");
	frases[3].id = 9;
	strcpy(frases[4].frase, "vasco");
	frases[4].id = 6;
	strcpy(frases[5].frase, "relva verde");
	frases[5].id = 3;
	strcpy(frases[6].frase, "chao preto");
	frases[6].id = 7;
	strcpy(frases[7].frase, "armario castanho");
	frases[7].id = 9;
	strcpy(frases[8].frase, "discos de ouro");
	frases[8].id = 8;
	strcpy(frases[9].frase, "dedos de goma");
	frases[9].id = 4;

	for (i=0; i < 10; i++) {
		sort[i] = frases[i];
	}


	quicksort(sort, 0, max);

	printf("\nquicksort: \n");

	for (i=0; i <= max; i++) {
		if (i < max) {
			printf("%d %s\n", sort[i].id, sort[i].frase);
		}
		else {			
			printf("%d %s\n", sort[i].id, sort[i].frase);
			
		}
	} 
	return 0;
}



/* funciona !!

void insertion(int a[], int l, int r) {
	int i,j;
	for (i = l+1; i <= r; i++) {
		int v = a[i];
		j = i-1;
			while ( j>=l && less(v ,a[j])) {
				a[j+1] = a[j];
				j--;
			}
		a[j+1] = v;
	}
} */