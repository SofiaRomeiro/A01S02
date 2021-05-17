#include <stdio.h>

void quicksort(char sort[], int l, int r) {
	/*
	* Function:  quicksort
	* --------------------
	* Quicksort algorithm
	*
	* Input  -> sort (task_t[]): list of tasks to sort
	*		 -> l (int): left limit
	*		 -> r (int): right limit
	*    
	*/
	int i;
	if (r <= l)
		return;
	i = partitionForStrings(sort, l, r);
	quicksort(sort, l, i-1);
	quicksort(sort, i+1, r);
}

int partitionForStrings(char sort[], int l, int r) {
	/*
	* Function:  partitionForStrings
	* --------------------
	* Adapted algorithm from the partition algorithm
	*
	* Input  -> sort (task_t[]): list of tasks to sort
	*		 -> l (int): left limit
	*		 -> r (int): right limit
	*   
	* Output -> the array's index were it was split
	*    
	*/
	int i = l-1; 
	int j = r; 
	char aux[200];
	strcpy(aux,sort[r].description); 
	while (i < j) { 				
		while (lessForStrings(sort[++i].description, aux));				
		while (lessForStrings(aux, sort[--j].description)) 
			if (j == l) 
				break;
		if (i < j)
			exchange(sort, i, j); 
	}
	exchange(sort, r, i);
	return i; 
}

int lessForStrings(char first[], char second[]) {
	/*
	* Function:  lessForStrings
	* --------------------
	* Compares two strings
	*
	* Input  -> first, second (char[]): strings to be compared 
	*   
	* Output -> if first is less than second
	*    
	*/
	return 1 ? (strcmp(first,second)<0) : 0;
}


int main () {
    char *a[10] = {"ola", "sou", "lula", "luis", "pedro", "vasco", "vodka", "madrid", "caramelo", "pila"};
    int n = sizeof a / sizeof a[0];
    quick_sort(a, n);

    printf("%s", a[9]);
    return 0;
}