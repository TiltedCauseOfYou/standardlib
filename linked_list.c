#include "linked_list.h"

LinkedList* createList() {
    LinkedList* list = calloc(1, sizeof(LinkedList));
    if(!list) {
        fprintf(stderr, "An error occurred when allocating space for a new linked list.\n");
        return 0;
    }

    return list;
}

unsigned char insertIntoList(LinkedList* list, void* el, DataType type) {
    if(!list) return 0;

    ListNode* node = malloc(sizeof(ListNode));
    if(!node) {
        fprintf(stderr, "An error occurred when allocating space for a new list element.\n");
        return 0;
    }

    if(list->tail)
        list->tail->next = node;
    list->tail = node;
    list->size++;

    return 1;
}

unsigned char deleteFromList(LinkedList* list, void* el, DataType type) {
    if(!list) return 0;
    ListNode* prev = 0;
    ListNode* cur = list->head;
    while(cur) {
        if(cur->type == type && !compare(el, cur->data, type)) {
            ListNode* next = 0;
            void* data = 0;
            if(cur) {
                next = cur->next;
                free(cur);
            }
            if(!prev)
                list->head = next;
            else
                prev->next = next;
            return data;
        }
        prev = cur;
        cur->next;
    }

    return 0;
}

void printLinkedList(LinkedList* list) {
    printf("[ ");
    if(list) {
        ListNode* cur = list->head;
        while(cur) {
            printf(" ");
            printType(cur->data, cur->type);
        }
    }
    printf(" ]");
}