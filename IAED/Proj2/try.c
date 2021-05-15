#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"
#define MAX_PATH

typedef struct node * node_s;

struct node {
    struct tree_node *current;
    struct node *next;
};

struct node* init() /* inicializa a pilha */ {
    struct node *top = NULL;
    return top;
}

void push(tree_node_s next, node_s top) /* introduz novo elemento no topo */ {
    struct node *new;
    new = (struct node *) malloc(sizeof(struct node));
    new->next->current = top;
    top = new;
}

int is_empty(node_s top) /* pergunta se está vazia */ {
    return top == NULL;
}

void pop(node_s top) /* apaga o topo e retorna o valor apagado */ {
    struct node *old;

    if (!is_empty(top)) {
        old->current = top;
        top = top->next;
        free(old);
        return;
    }
    else
        return;
}






int main() {

    // len 11

    char *teste;
    char *pila;
    teste = (char*) malloc(sizeof(char)*12);

    strcpy(teste, "ola bom dia");

    pila = teste;

    free(pila);

    return 0;
}