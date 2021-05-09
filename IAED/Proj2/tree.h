#ifndef __TREE_H__
#define __TREE_H__

typedef struct tree_node {
    char *path;
    char *value;
    struct list_node_s *childs; 
} *tree_node_s;

#endif