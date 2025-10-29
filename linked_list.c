#include "linked_list.h"
#include <unistd.h>

LinkedList* createList() {
    LinkedList* list = calloc(1, sizeof(LinkedList));
    if(!list) {
        fprintf(stderr, "An error occurred when allocating space for a new linked list.\n");
        return 0;
    }

    return list;
}


LinkedList* connect(LinkedList* list1, LinkedList* list2) {
    if(!list1 || !list2) return 0;

    LinkedList* list = createList();
    if(!list) {
        fprintf(stderr, "An error occured when allocating space for a new Linked List, connecting two other lists-\n");
        return 0;
    }

    if(!list1->head) {
        if(list2->head) {
            list->head = list->tail = list2->head;
            list->size = list2->size;
            free(list2);
        }
        return list;
    }
    else if(!list2->head) {
            list->head = list->tail = list1->head;
            list->size = list1->size;
            free(list1);
            return list;
    }

    list->head = list1->head;
    list1->tail->next = list2->head;
    list->tail = list2->tail;
    list->size = list1->size + list2->size;

    return list;
}

unsigned char insertNode(LinkedList* list, ListNode* node) {
    if(!list || !node) return 0;

    if(!list->head) {
        list->head = node;
    }
    if(list->tail)
        list->tail->next = node;
    list->tail = node;
    list->size++;

    return 1;
}

unsigned char insertIntoList(LinkedList* list, void* el, DataType type) {
    if(!list) return 0;

    ListNode* node = malloc(sizeof(ListNode));
    if(!node) {
        fprintf(stderr, "An error occurred when allocating space for a new list element.\n");
        return 0;
    }
    node->data = el;
    node->type = type;
    node->next = 0;

    return insertNode(list, node);
}

void* deleteFromList(LinkedList* list, void* el, DataType type) {
    if(!list || !list->size) return 0;
    ListNode* prev = 0;
    ListNode* cur = list->head;
    while(cur) {
        if(cur->type == type && !compare(el, cur->data, type)) {
            ListNode* next = 0;
            void* data = 0;
            if(cur) {
                data = cur->data;
                next = cur->next;
                free(cur);
            }
            if(!prev)
                list->head = next;
            else
                prev->next = next;
            list->size--;
            return data;
        }
        prev = cur;
        cur = cur->next;
    }

    return 0;
}

void printLinkedList(LinkedList* list) {
    printf("[");
    if(list) {
        ListNode* cur = list->head;
        if(cur) {
            while(1) {
                printTypeBlank(cur->data, cur->type);
                cur = cur->next;
                if(cur) {
                    printf(", ");
                    continue;
                }
                break;
            }
        }
    }
    printf("]\n");
    fflush(stdout);
}

void printLinkedListCustom(LinkedList* list, void (*printEl)(void* el)) {
    printf("[");
    if(list) {
        ListNode* cur = list->head;
        if(cur) {
            while(1) {
                printEl(cur->data);
                cur = cur->next;
                if(cur) {
                    printf(", ");
                    continue;
                }
                break;
            }
        }
    }
    printf("]\n");
    fflush(stdout);
}

unsigned char exists(LinkedList* list, void* el, unsigned char (*equal)(void* el1, void* el2)) {
    if(!list) return 0;
    ListNode* cur = list->head;
    while(cur) {
        if(equal(el, cur->data)) return 1;
        cur = cur->next;
    }

    return 0;
}

void* find(LinkedList* list, void* el, unsigned char (*equal)(void* el1, void* el2)) {
    if(!list) return 0;
    ListNode* cur = list->head;
    while(cur) {
        if(equal(el, cur->data)) return cur->data;
        cur = cur->next;
    }

    return 0;
}

void freeList(LinkedList* list) {
    if(list) {
        ListNode* cur = list->head;
        while(cur) {
            ListNode* next = cur->next;
            free(cur);
            cur = next;
        }
    }
    free(list);
}

void freeListCustom(LinkedList* list, void (*freeData)(void* data)) {
    if(list) {
        ListNode* cur = list->head;
        while(cur) {
            ListNode* next = cur->next;
            if(cur->data) freeData(cur->data);
            free(cur);
            cur = next;
        }
        free(list);
    }
}

void freeListFull(LinkedList* list) {
    if(list) {
        ListNode* cur = list->head;
        while(cur) {
            ListNode* next = cur->next;
            if(cur->data) free(cur->data);
            free(cur);
            cur = next;
        }
        free(list);
    }
}