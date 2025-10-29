#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "data.h"
#include "linked_list.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct Data {
    size_t keySize;
    void* key;
    void* data;
    DataType keyType;
    DataType type;
} Data;

/* typedef struct dynamArr {
    size_t size;
    size_t i;
    Data** data;
} dynamArr; */

typedef struct HashTable {
    size_t size;
    size_t insertCount;
    LinkedList** table;
    DataType type;
} HashTable;

uint32_t hash(char* key, size_t n, size_t m);

HashTable* createHashTable(uint32_t minSize);
uint8_t insert(HashTable* table, char* key, size_t keySize, DataType keyType, void* data, DataType type);
void* get(HashTable* table, char* key, size_t keySize);

void printTable(HashTable* table);
void printBuckets(HashTable* table);
void freeTable(HashTable* table);

#endif