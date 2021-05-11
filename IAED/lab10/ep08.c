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

#define MAX 10

typedef struct next {
    int value;
    struct next *next;
} Next;

Next *hash[MAX];

int hashing(int val) { return val % MAX; }

int maxcollision() {



    return ;
}

