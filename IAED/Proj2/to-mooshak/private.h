#ifndef __STRUCTS_H__
#define __STRUCTS_H__

struct tree_node {
    char *path;
    char *value;
    int num_of_children;
    struct tree_node *parent;
    struct tree_node *brother;
    struct tree_node *child; 
};

struct stack_node{
    struct tree_node *current;
    struct stack_node *previous, *next;
};

struct stack {
    struct stack_node *head;
    struct stack_node *tail;
};


#endif