#ifndef __PUBLIC_H__
#define __PUBLIC_H__

typedef struct tree_node* tree_node_s;
typedef struct stack* stack_s;

/* main.c */
char *read_line();
char *read_command(char *buffer);
int aux(char buffer[]);
void clear(char string[]);
int strcompare(char str1[], char str2[]);

/* tree.c */
tree_node_s treeConstructor();
tree_node_s newTreeNode();
tree_node_s treePartialDestructor(tree_node_s node);
tree_node_s treeCompletlyDestructor(tree_node_s node);
void treeAdd(tree_node_s root, char buffer[]);

void treeAdd(tree_node_s root, char buffer[]);
tree_node_s auxAddTree(tree_node_s parent, char path[]) ;
tree_node_s findBrotherNode(tree_node_s current);
tree_node_s newChild(char path[]);
tree_node_s brotherSearch(tree_node_s child, char path[]);

stack_s treePrint(tree_node_s root, stack_s top);
void treeFind(tree_node_s root, char buffer[]);
tree_node_s treeSearch(tree_node_s root, char buffer[], stack_s top);
void printFuncStack(stack_s stack);
void treeList(tree_node_s root, char buffer[]);
tree_node_s treeDelete(tree_node_s root, char buffer[]);


tree_node_s findParent(tree_node_s current, stack_s stack);



/* list.c*/

void printList(stack_s head);
void removeEnd(stack_s head); 
void destroyList(stack_s list);
void destroyStack(stack_s stack);
void printStack(stack_s top);


stack_s initStack();
stack_s push(tree_node_s next, stack_s top);
int is_empty(stack_s top);
stack_s pop(stack_s top);


int countNodes(tree_node_s root);
tree_node_s nodeSearch(tree_node_s root, char buffer[]);

void exchange(tree_node_s sort[], int i, int j);
int less(tree_node_s first, tree_node_s second);
int partition(tree_node_s sort[], int l, int r);
void quicksort(tree_node_s sort[], int l, int r);


#endif