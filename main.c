// #include "vector.h"
#include "hash.h"
// #include "linked_list.h"

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

    int n = 1;
    HashTable* table = createHashTable(n);
    while(table->insertCount <= 100) {
        int* num = malloc(sizeof(int));
        *num = n++;
        insert(table, (char*) &num, sizeof(int), INT, &num, INT);
    }
    printf("%lf\n", (((double) countTotalCollisions(table) / table->insertCount)) * 100);
    fflush(stdout);
    while(table->insertCount <= 1000) {
        int* num = malloc(sizeof(int));
        *num = n++;
        insert(table, (char*) &num, sizeof(int), INT, &num, INT);
    }
    printf("%lf\n", (((double) countTotalCollisions(table) / table->insertCount)) * 100);
    fflush(stdout);
    while(table->insertCount <= 10000) {
        int* num = malloc(sizeof(int));
        *num = n++;
        insert(table, (char*) &num, sizeof(int), INT, &num, INT);
    }
    printf("%lf\n", (((double) countTotalCollisions(table) / table->insertCount)) * 100);
    fflush(stdout);
    while(table->insertCount <= 100000) {
        int* num = malloc(sizeof(int));
        *num = n++;
        insert(table, (char*) &num, sizeof(int), INT, &num, INT);
    }
    printf("%lf\n", (((double) countTotalCollisions(table) / table->insertCount)) * 100);
    fflush(stdout);
    while(table->insertCount <= 1000000) {
        int* num = malloc(sizeof(int));
        *num = n++;
        insert(table, (char*) &num, sizeof(int), INT, &num, INT);
    }
    printf("%lf\n", (((double) countTotalCollisions(table) / table->insertCount)) * 100);
    
    printf("\n\n");
    fflush(stdout);

    freeTable(table);

    /* LinkedList* list = createList();
    printLinkedList(list);


    for(size_t i = 0; i < 10; i++) {
        int* num = malloc(sizeof(int));
        *num = i;
        insertIntoList(list, num, INT);
        printLinkedList(list);
    }
    int num = 3;
    int* el = deleteFromList(list, &num, INT);
    if(el) free(el);
    printLinkedList(list);
    num = 5;
    el = deleteFromList(list, &num, INT);
    if(el) free(el);
    printLinkedList(list);

    freeListFull(list); */

    return 0;
}
