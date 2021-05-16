#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"

struct node* init() /* inicializa a pilha */ {
    struct node *top = NULL;
    return top;
}

node_s push(tree_node_s adding, node_s top) /* introduz novo elemento no topo */ {
    struct node *new;
    new = (struct node *) malloc(sizeof(struct node));
    new->current = adding;
    new->next = top;
    top = new;
    return top;
}

int is_empty(node_s top) /* pergunta se está vazia */ {
    return top == NULL;
}

node_s pop(node_s top) /* apaga o topo e retorna o valor apagado */ {
    struct node *old;

    if (!is_empty(top)) {
        old = top;
        top = top->next;
        free(old);
        return top;
    }
    else
        return NULL;
}
