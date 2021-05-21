#ifndef __PUBLIC_H__
#define __PUBLIC_H__

typedef struct tree_node * tree_node_s;
typedef struct list_node * list_node_s;
typedef struct listExtremes * list_ext_s;

#define ROOT "/"
#define MAX_PATH 65529
#define MAX_COMMAND_LEN 6
#define SPACE ' ' || '\t'
#define equals(A,B) !(strcmp(A,B)

enum commands {HELP, QUIT, SET, PRINT, FIND, LIST, LISTNOARG, SEARCH, DELETE, NONE};

/* MAIN */
int switchForCommand();
void clear(char string[]);
void readValue(char buffer[]);

/* COMMANDS */

/* TREE */
tree_node_s treeConstructor();
tree_node_s newTreeNode(char path[], char value[], tree_node_s parent);
tree_node_s treeCompletlyDestructor(tree_node_s node);
tree_node_s treePartialDestructor(tree_node_s node);
void treeAdd(tree_node_s root);
tree_node_s auxAddTree(tree_node_s parent, char path[]);
tree_node_s brotherSearch(tree_node_s current, char path[]);
tree_node_s treeSearch(tree_node_s root, char buffer[], list_ext_s extremes, list_node_s head);
void treeFind(tree_node_s root);
list_ext_s treePrint(tree_node_s root, list_ext_s extremes, list_node_s head);
tree_node_s findParent(tree_node_s current, list_ext_s extremes);
void listRoot(tree_node_s root);
void treeList(tree_node_s root, int args);
tree_node_s nodeSearch(tree_node_s root, char directory[]);
tree_node_s treeDelete(tree_node_s root);


/* STACK */
list_node_s insertEnd(list_ext_s extremes, list_node_s head, tree_node_s tree_node);
list_node_s deleteEnd(list_ext_s extremes, list_node_s head);
void printList(list_ext_s extremes);
void printSearch(list_ext_s extremes);
void destroyList(list_ext_s extremes);


/* SORT */
void exchange(tree_node_s sort[], int i, int j);
int less(tree_node_s first, tree_node_s second);
int partition(tree_node_s sort[], int l, int r);
void quicksort(tree_node_s sort[], int l, int r);
int countNodes(tree_node_s root);

#endif