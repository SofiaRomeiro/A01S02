#ifndef __STRUCTS_H__
#define __STRUCTS_H__

struct tree_node {
    char *path;
    char *value;
    struct tree_node *brother;
    struct tree_node *child; 
};

#endif