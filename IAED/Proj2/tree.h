#ifndef __TREE_H__
#define __TREE_H__


typedef struct tree_node* tree_node_s;

tree_node_s treeConstructor();
tree_node_s newTreeNode();
void treeDestructor(tree_node_s node);
void treeAdd(tree_node_s root, char buffer[]);
tree_node_s auxAddTree(tree_node_s parent, char directory[]);



#endif