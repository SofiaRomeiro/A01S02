#ifndef __STRUCTS_H__
#define __STRUCTS_H__

struct list_node {
    struct tree_node *tree_node;
    struct list_node *next;
};

struct tree_node {
    char *path;
    char *value;
    struct list_node *childs; 
};


struct dir {
    char *name;
    struct dir *next;
};

struct input {
    char *value;
    struct dir *path;
};

#endif