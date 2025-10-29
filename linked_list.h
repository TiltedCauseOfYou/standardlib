#include <stdlib.h>
#include <stdio.h>
#include "data.h"

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
void* deleteFromList(LinkedList* list, void* el, DataType type);
void printLinkedList(LinkedList* list);
void printLinkedListCustom(LinkedList* list, void (*printEl)(void* el));
void freeList(LinkedList* list);
void freeListCustom(LinkedList* list, void (*freeData)(void* data));
void freeListFull(LinkedList* list);
LinkedList* connect(LinkedList* list1, LinkedList* list2);
LinkedList* connectFully(LinkedList* list1, LinkedList* list2);
unsigned char exists(LinkedList* list, void* el, unsigned char (*equal)(void* el1, void* el2));
void* find(LinkedList* list, void* el, unsigned char (*equal)(void* el1, void* el2));

#endif