#ifndef __PUBLIC_H__
#define __PUBLIC_H__

typedef struct tree_node* tree_node_s;
typedef struct list_node* list_node_s;

tree_node_s treeConstructor();
tree_node_s newTreeNode();
void treeDestructor(tree_node_s node);
void treeAdd(tree_node_s root, char buffer[]);
tree_node_s auxAddTree(tree_node_s parent, char directory[]);


list_node_s listConstructor();
void listDestructor(list_node_s node);
tree_node_s listSearch(list_node_s list, char *target_dir);



#endif