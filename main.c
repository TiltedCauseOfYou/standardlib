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

    do {
        int* num = malloc(sizeof(int));
        *num = n++;
        insert(table, (char*) num, sizeof(int), INT, num, INT);
    } while(((double) (table->insertCount+1)) / table->size < 0.75);
    printf("%lf\n", (((double) countTotalCollisions(table)) / table->insertCount) * 100);
    fflush(stdout);
    do {
        int* num = malloc(sizeof(int));
        *num = n++;
        insert(table, (char*) num, sizeof(int), INT, num, INT);
    } while(((double) (table->insertCount+1)) / table->size < 0.75);
    printf("%lf\n", (((double) countTotalCollisions(table)) / table->insertCount) * 100);
    fflush(stdout);
    do {
        int* num = malloc(sizeof(int));
        *num = n++;
        insert(table, (char*) num, sizeof(int), INT, num, INT);
    } while(((double) (table->insertCount+1)) / table->size < 0.75);
    printf("%lf\n", (((double) countTotalCollisions(table)) / table->insertCount) * 100);
    fflush(stdout);
    do {
        int* num = malloc(sizeof(int));
        *num = n++;
        insert(table, (char*) num, sizeof(int), INT, num, INT);
    } while(((double) (table->insertCount+1)) / table->size < 0.75);
    printf("%lf\n", (((double) countTotalCollisions(table)) / table->insertCount) * 100);
    fflush(stdout);
    do {
        int* num = malloc(sizeof(int));
        *num = n++;
        insert(table, (char*) num, sizeof(int), INT, num, INT);
    } while(((double) (table->insertCount+1)) / table->size < 0.75);
    printf("%lf\n", (((double) countTotalCollisions(table)) / table->insertCount) * 100);
    do {
        int* num = malloc(sizeof(int));
        *num = n++;
        insert(table, (char*) num, sizeof(int), INT, num, INT);
    } while(((double) (table->insertCount+1)) / table->size < 0.75);
    printf("%lf\n", (((double) countTotalCollisions(table)) / table->insertCount) * 100);
    do {
        int* num = malloc(sizeof(int));
        *num = n++;
        insert(table, (char*) num, sizeof(int), INT, num, INT);
    } while(((double) (table->insertCount+1)) / table->size < 0.75);
    printf("%lf\n", (((double) countTotalCollisions(table)) / table->insertCount) * 100);
    do {
        int* num = malloc(sizeof(int));
        *num = n++;
        insert(table, (char*) num, sizeof(int), INT, num, INT);
    } while(((double) (table->insertCount+1)) / table->size < 0.75);
    printf("%lf\n", (((double) countTotalCollisions(table)) / table->insertCount) * 100);
    
    printf("\n");
    fflush(stdout);

    table = createHashTable(1);

    for(int i = 0; i < 100; i++) {
        int* num = malloc(sizeof(int));
        *num = i;
        insert(table, (char*) num, sizeof(int), INT, num, INT);
    }
    printf("%lf\n", (((double) countTotalCollisions(table)) / ((double) table->insertCount)) * 100.0);

    for(int i = 100; i < 1000; i++) {
        int* num = malloc(sizeof(int));
        *num = i;
        insert(table, (char*) num, sizeof(int), INT, num, INT);
    }
    printf("%lf\n", (((double) countTotalCollisions(table)) / ((double) table->insertCount)) * 100.0);

    for(int i = 1000; i < 10000; i++) {
        int* num = malloc(sizeof(int));
        *num = i;
        insert(table, (char*) num, sizeof(int), INT, num, INT);
    }
    printf("%lf\n", (((double) countTotalCollisions(table)) / ((double) table->insertCount)) * 100.0);

    for(int i = 10000; i < 100000; i++) {
        int* num = malloc(sizeof(int));
        *num = i;
        insert(table, (char*) num, sizeof(int), INT, num, INT);
    }
    printf("%lf\n\n\n", (((double) countTotalCollisions(table)) / ((double) table->insertCount)) * 100.0);

    /* for(int i = 100000; i < 1000000; i++) {
        int* num = malloc(sizeof(int));
        *num = i;
        insert(table, (char*) num, sizeof(int), INT, num, INT);
    }
    printf("%lf\n", (((double) countTotalCollisions(table)) / table->insertCount) * 100);
    
    printf("\n\n");
    fflush(stdout); */
    // freeTable(table);
}

int main(__attribute__ ((unused)) int argc, __attribute__ ((unused)) char const *argv[])
{
    printf("mul:\n");
    testHashingDist();
    incHashSwitch();
    printf("fnv:\n");
    testHashingDist();
    incHashSwitch();
    printf("djb2:\n");
    testHashingDist();
    incHashSwitch();
    printf("sbdm:\n");
    testHashingDist();
    incHashSwitch();
    printf("joaat:\n");
    testHashingDist();

    return 0;
}
