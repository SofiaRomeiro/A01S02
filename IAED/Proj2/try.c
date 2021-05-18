#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "public.h"
#include "private.h"

void exchange(tree_node_s sort[], int i, int j) {

	tree_node_s aux;
	aux = sort[i];
	sort[i] = sort[j];
	sort[j] = aux; 
}

int less(tree_node_s first, tree_node_s second) {

	return 1 ? (strcmp(first->path,second->path)<0) : 0;
}

int partition(tree_node_s sort[], int l, int r) {

	int i = l-1; 
	int j = r; 
	tree_node_s aux;
	aux = sort[r]; 
	while (i < j) { 				
		while (lessForStrings(sort[++i], aux));				
		while (lessForStrings(aux, sort[--j])) 
			if (j == l) 
				break;
		if (i < j)
			exchange(sort, i, j); 
	}
	exchange(sort, r, i);
	return i; 
}

void quicksort(tree_node_s sort[], int l, int r) {

	int i;
	if (r <= l)
		return;
	i = partitionForStrings(sort, l, r);
	quicksort(sort, l, i-1);
	quicksort(sort, i+1, r);
}

int main () {
    tree_node_s a[10];
	int i=0;
	
	while(i<10) {
		a[i] = (tree_node_s)malloc(sizeof(struct tree_node));
		a[i]->path = (char *) malloc(sizeof(char)*30);
		scanf("%s", a[i]->path);
		i++;
	}	

    quicksort(a, 0, 9);

	for (i=0; i<10; i++) {
		printf("%s\n", a[i]->path);
	}

    return 0;
}