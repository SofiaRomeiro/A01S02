#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct str_node  {
    struct str_node *next, *previous;
    char c;
} node;

typedef struct  {
    struct str_node *head, *last;
} list;

list *mk_list(){
    list *new_list = malloc(sizeof(list));
    new_list->head = NULL;
    new_list->last = NULL;
    return new_list;
}

void free_list(list *l) {

    while (l->head != NULL) {
        node *next = l->head->next;
        free(l->head);       
        l->head = next;
    }
    free(l);
}

void add_last(list *l, char c) {

    node *new_node = malloc(sizeof(node));
    new_node->c = c;
    new_node->previous = l->last;
    if (l->last != NULL) {
        l->last->next = new_node;
    }
    else {
        l->head = new_node;
    }

    l->last = new_node;
}

int is_paly(const list *ls) {
    
    node *next, *prev;

    next = ls->head;
    prev = ls->last;

    while (next != NULL && prev != NULL) {
        if (next->c != prev->c) {
            return 0;
        }
        next = next->next;
        prev = prev->previous;
    }

    return next == prev;
}

int main() {
    return 0;
}