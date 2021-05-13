/* II

Answer : 

pos  |   values
---- | -----------
  0  |  27->18->
  1  |     X
  2  |     X
  3  |  30->21
  4  |  13
  5  |  14
  6  |  15
  7  |     X
  8  |     X

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef struct next {
    int value;
    struct next *next;
} Next;

Next *hash[MAX];

int hashing(int val) { return val % MAX; }

int lower() {
  int lower = hash[0]->value, iter = 0;
  Next * aux;

  while (iter < MAX) {
    aux = hash[iter];
    for(; aux != NULL; aux = aux->next) {
        if (aux->value < lower) {
          lower = aux->value;
        }
    }
    iter++;  
  }
  return lower;
}

int maxcollision() {

  int max=0, iter=0, i;
  Next *aux;

    while (iter < MAX) {
      aux = hash[iter];
      for (i=0; aux != NULL; aux = aux->next, i++);
      if (i > max) {
        max = i;
      }
    iter++;
    }
  
  return max-1;
}


Next * insertBegin(Next *head, int a) {
  Next * new = (Next *)malloc(sizeof(struct next));
  new->value = a;
  new->next = head;
  return new;
}

void Init() {
  int i;
  *hash = (Next *)malloc(MAX * sizeof(struct next));
  for (i = 0; i < MAX; i++) hash[i] = NULL;
}

void STinsert(int num) {
  int i = hashing(num);
  hash[i] = insertBegin(hash[i], num);
}

int main() {

  int i;
  Init();

  while (scanf("%d\n", &i)) {
    STinsert(i);
  }

  printf("lower = %d\n", lower());
  return 0;
}


