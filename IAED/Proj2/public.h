#ifndef __PUBLIC_H__
#define __PUBLIC_H__

typedef struct tree_node* tree_node_s;
typedef struct node* node_s;
typedef struct list *list_s;



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
tree_node_s treeSearch(tree_node_s root, char buffer[], node_s top);
void Printer(node_s top);

tree_node_s treeSearchL(tree_node_s root, char buffer[], list_s list);


/* list.c*/


list_s initList();
list_s insertBegin(list_s head, tree_node_s node);
list_s insertEnd(list_s head, tree_node_s node);
void printList(list_s head);
void removeEnd(list_s head); 
void destroyList(list_s list);
void destroyStack(node_s stack);

node_s init();
node_s push(tree_node_s next, node_s top);
int is_empty(node_s top);
node_s pop(node_s top);


#endif