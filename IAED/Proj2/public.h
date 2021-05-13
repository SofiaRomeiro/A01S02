#ifndef __PUBLIC_H__
#define __PUBLIC_H__

typedef struct tree_node* tree_node_s;
typedef struct list_node* list_node_s;


/* main.c */
char *read_line();
char *read_command(char *buffer);
int aux();
void read(char buffer[]);
void clear(char string[]);
void printTest(tree_node_s root);

/* tree.c */
tree_node_s treeConstructor();
tree_node_s newTreeNode();
void treeDestructor(tree_node_s node);
void treeAdd(tree_node_s root, char buffer[]);

void treeAdd(tree_node_s root, char buffer[]);
tree_node_s auxAddTree(tree_node_s parent, char path[]) ;
tree_node_s findBrotherNode(tree_node_s current, char path[]);
tree_node_s newChild(char path[]);
tree_node_s brotherSearch(tree_node_s child, char path[]);

void treePrint(tree_node_s root);
void treeFind(tree_node_s root, char buffer[]);



/* list.c*/
list_node_s listConstructor();
void listDestructor(list_node_s node);
tree_node_s listSearch(list_node_s children_list, char *target_dir);
tree_node_s listFind(list_node_s children, char *target_dir);
list_node_s isItBrother(list_node_s children_list);


#endif