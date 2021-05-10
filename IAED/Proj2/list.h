#ifndef __LIST_H__
#define __LIST_H__

typedef struct list_node* list_node_s;

list_node_s listConstructor();
void listDestructor(list_node_s node);

#endif