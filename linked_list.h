#include <stdlib.h>
#include <stdio.h>
#include "Data.h"

#ifndef LINKED_LIST_H
#define LINKED_LIST_H


typedef struct linked_list_node {
    struct linked_list_node* next;
    void* data;
    DataType type;
} ListNode;
typedef struct linked_list {
    size_t size;
    ListNode* head;
    ListNode* tail;
} LinkedList;

LinkedList* createList();
unsigned char insertIntoList(LinkedList* list, void* el, DataType type);
unsigned char deleteFromList(LinkedList* list, void* el, DataType type);
void printLinkedList(LinkedList* list);

#endif