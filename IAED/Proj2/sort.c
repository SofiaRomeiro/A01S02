#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"

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
		while (less(sort[++i], aux));				
		while (less(aux, sort[--j])) 
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
	i = partition(sort, l, r);
	quicksort(sort, l, i-1);
	quicksort(sort, i+1, r);
}


int countNodes(tree_node_s root) {
    int counter;
    tree_node_s aux=root;
	printf("[countNodes]estou onde? %s\n", root->path);
    for (counter=0; aux != NULL; counter++, aux = aux->brother);
    return counter;
}
