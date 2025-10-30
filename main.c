// #include "vector.h"
#include "hash.h"
// #include "linked_list.h"

void testLinkedListFunc() {
    LinkedList* list = createList();
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

    freeListFull(list);
}

void testHashFunc() {
}

void testHashingDist() {
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

    // freeTable(table);
}

int main(__attribute__ ((unused)) int argc, __attribute__ ((unused)) char const *argv[])
{
    testHashingDist();

    return 0;
}
