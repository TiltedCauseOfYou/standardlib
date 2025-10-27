#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef enum DataType {
    INT,
    INT32,
    UINT32,
    INT64,
    UINT64,
    FLOAT,
    DOUBLE,
    POINTER
} DataType;

typedef struct Data {
    size_t keySize;
    void* key;
    void* data;
    DataType type;
} Data;

typedef struct dynamArr {
    size_t size;
    size_t i;
    Data** data;
} dynamArr;

typedef struct HashTable {
    size_t size;
    size_t insertCount;
    dynamArr** table;
    DataType type;
} HashTable;

uint32_t hash(char* key, size_t n, size_t m);

HashTable* createHashTable(uint32_t minSize);
uint8_t insert(HashTable* table, char* key, size_t keySize, void* data, DataType type);

void printTable(HashTable* table);
void freeTable(HashTable* table);

#endif