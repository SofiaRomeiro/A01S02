#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct next *link;

typedef struct next {
    int value;
    struct next *next;
} Next;

int upto(Next *head, int val) {
    int count=0;
    if (head==NULL) {
        return 0;
    }
    while (head != NULL) {
        if (head->value == val) {
            return count;
        }
        count++;
        head = head->next;
    }
    return count;
}

Next *removeAfterValue(Next *head, int val) {
    link newhead = head;
    if (head == NULL) { return head;}
    while (newhead != NULL) {
        if (newhead->value == val) {
            return newhead;
        }
        newhead = newhead->next;
    }
    return head;
}


int main() {

    int num, count=0;
    link head = (link)malloc(sizeof(link)); 
    link aux = (link)malloc(sizeof(link));
    return 0;
}
