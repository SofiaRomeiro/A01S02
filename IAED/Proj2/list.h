#ifndef __LIST_H__
#define __LIST_H__

#include "tree.h"

typedef struct list_node* list_node_s;
list_node_s listConstructor();
void listDestructor(list_node_s node);
tree_node_s listSearch(list_node_s list, char *target_dir);


#endif