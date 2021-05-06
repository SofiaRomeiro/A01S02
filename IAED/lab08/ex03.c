#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_OPENING(C) C == '(' || C == '[' || C == '{'
#define IS_CLOSING(C) C == ')' || C == ']' || C == '}'

typedef struct {
    int *v;     /* contents of the stack */
    int cap;    /* capacity of v, i.e. how many elements can fit in v */
    int sz;     /* number of elements currently stored in v */
} stack;

stack *init() {

    stack *s;
    s = (stack *)malloc(sizeof(stack));
    s->v = malloc(sizeof(int)*4);
    s->cap = 4;
    s->sz = 0;

    return s;
}

void push(stack *s, int e) {

    if (s->sz == s->cap) {
        s->v = realloc(s, sizeof(int)*((s->cap)+1));
    }

    s->v[s->sz] = e;
    s->sz++;
}

int pop(stack *s) {

    s->sz = (s->sz)-1;
    return s->v[s->sz];

}

int is_empty(stack *s) {
    return !s->sz;
}

void destroy(stack *s) {
    free(s->v);
    free(s);
}

int main() {

    char c;
    stack *s = init();
    char match;

    while ((c=getchar()) != EOF && c!= '\n') {

        if (IS_OPENING(c)) {
            push(s, c);
        }
        else if (IS_CLOSING(c)) {

            if (c==')') match = '(';
            else if (c==']') match = '[';
            else match = '{';

            if (match != pop(s)) {
                printf("no\n");
                return 0;
            }    

        }
    }

    printf(is_empty(s) ? "yes\n" : "no\n");

    return 0;
}

