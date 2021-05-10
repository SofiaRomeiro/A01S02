#ifndef __TREE_H__
#define __TREE_H__

#include "directory.h"

typedef struct tree_node* tree_node_s;

tree_node_s treeConstructor();
void treeDestructor(tree_node_s node);
void treeAdd(tree_node_s root, input_s newinput);



#endif