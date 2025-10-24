#include <stdint.h>

#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef enum DataType DataType;
typedef struct HashTable Hashtable;

uint32_t hashInt(int key, uint32_t m);
uint32_t hash(void* key, uint32_t n, int m);

HashTable* createHashTable(uint32_t minSize, DataType type);
void insert(HashTable* table, void* el, DataType type);

#endif