// #include "vector.h"
// #include "hash.h"
#include "linked_list.h"

int main(__attribute__ ((unused)) int argc, __attribute__ ((unused)) char const *argv[])
{
    /* vec32* vec = newVec();

    for(int i = 1; i < 51; i++) {
        append(vec, i);
        printVec(vec);
    }

    for(int i = 0; i < 50; i++) {
        printf("%d", pop(vec));
        printVec(vec);
    }

    freeVec(vec); */

    /* HashTable* table = createHashTable(10);
    for(int i = 0; i < 10; i++) {
        int* num = malloc(sizeof(int));
        *num = i;
        insert(table, (char*) num, sizeof(int), INT, num, INT);
    }

    printTable(table);

    freeTable(table); */

    LinkedList* list = createList();
    printLinkedList(list);

    for(size_t i = 0; i < 10; i++) {
        int* num = malloc(sizeof(int));
        *num = i;
        insertIntoList(list, num, INT);
        printLinkedList(list);
    }
    for(size_t i = 0; i < 10; i++) {
        int* num = malloc(sizeof(int));
        *num = i;
        deleteFromList(list, num, INT);
        free(num);
        printLinkedList(list);
    }

    return 0;
}
