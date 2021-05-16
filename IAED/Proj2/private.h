#ifndef __STRUCTS_H__
#define __STRUCTS_H__

struct tree_node {
    char *path;
    char *value;
    struct tree_node *parent;
    struct tree_node *brother;
    struct tree_node *child; 
};

struct list_node {
    struct tree_node *current;
    struct list_node *next;
};

struct node{
    struct tree_node *current;
    struct node *next;
};

struct list {
    struct tree_node *current;
    struct list *previous, *next;
};

#endif