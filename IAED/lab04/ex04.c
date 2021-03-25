#include <stdio.h>
#include <string.h>
#define MAX 80

int palyndrome(char s[]) {

	int size = strlen(s);
	int i;

	for (i=0; i < size/2; ++i) {
		if (s[i] != s[size-i-1]) {
			return 0;
		}	
	}
	return 1;
}

int main() {

	char s[MAX];
	
	printf("word ?\n");
	scanf("%s", s);

	printf(palyndrome(s) == 1 ? "yes" : "no");

	return 0;
}

