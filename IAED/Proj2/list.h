#ifndef __LIST_H__
#define __LIST_H__

typedef struct list_node {
    tree_node_s *child;
    struct list_node_s *next;
} *list_node_s;

#endif