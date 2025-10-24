#include <stdio.h>
#include <math.h>

#include "hash.h"

enum DataType {
    INT,
    INT32,
    UINT32,
    INT64,
    UINT64,
    FLOAT,
    DOUBLE,
    POINTER
};

typedef struct Data {
    DataType keyType;
    DataType type;
    void* key;
    void* data;
} Data;

typedef struct HashTable {
    DataType type;
    size_t size;
    dynamArr** table;
} HashTable;

typedef struct dynamArr {
    size_t size;
    size_t i;
    DataType type;
    void* data;
} dynamArr;

uint8_t sizeOfType(DataType type) {
    switch(type) {
        case INT:
            return sizeof(int);
        case INT32:
        case UINT32:
            return 4;
        case INT64:
        case UINT64:
            return 8;
        case DOUBLE:
            return sizeof(double);
        case FLOAT:
            return sizeof(float);
        case(POINTER):
            return sizeof(char*);
        default:
            fprintf(stderr, "%s is an unknown datatype.\n", type);
            return 0;
    }
}
void* findIn(dynamArr* arr, void* el, DataType type) {
    switch(type) {
        case INT:
            int* typeArr = (int*) arr->data;
            for(size_t i = 0; i < arr->i; i++) {
                if(typeArr[i] == *((int*) el)) return typeArr + i;
            }
            return 0;
        case INT32:
            int32_t* typeArr = (int32_t*) arr->data;
            for(size_t i = 0; i < arr->i; i++) {
                if(typeArr[i] == *((int32_t*) el)) return typeArr + i;
            }
            return 0;
        case UINT32:
            uint32_t* typeArr = (uint32_t*) arr->data;
            for(size_t i = 0; i < arr->i; i++) {
                if(typeArr[i] == *((uint32_t*) el)) return typeArr + i;
            }
            return 0;
        case INT64:
            int64_t* typeArr = (int64_t*) arr->data;
            for(size_t i = 0; i < arr->i; i++) {
                if(typeArr[i] == *((int64_t*) el)) return typeArr + i;
            }
            return 0;
        case UINT64:
            uint64_t* typeArr = (uint64_t*) arr->data;
            for(size_t i = 0; i < arr->i; i++) {
                if(typeArr[i] == *((uint64_t*) el)) return typeArr + i;
            }
            return 0;
        case FLOAT:
            float* typeArr = (float*) arr->data;
            for(size_t i = 0; i < arr->i; i++) {
                if(typeArr[i] == *((float*) el)) return typeArr + i;
            }
            return 0;
        case DOUBLE:
            double* typeArr = (double*) arr->data;
            for(size_t i = 0; i < arr->i; i++) {
                if(typeArr[i] == *((double*) el)) return typeArr + i;
            }
            return 0;
        case POINTER:
            char** typeArr = (char**) arr->data;
            for(size_t i = 0; i < arr->i; i++) {
                if(typeArr[i] ==  el) return typeArr + i;
            }
            return 0;
        default:
            fprintf(stderr, "%s is an unknown datatype.\n", type);
    }
}
void* insertInto(dynamArr* arr, void* el, DataType type) {
    if(arr->size == arr->i) {
        arr->data = realloc(sizeOfType(type) * arr->size * 2);
        if(!arr->data) {
            fprintf(stderr, "An error occured when reallocating space for a HashTable of size %d to size %d, with an element size of %d (%d bytes -> %d bytes).\n",
            arr->size, sizeOfType(arr->size * 2), sizeOfType(type) * arr->size, sizeOfType(type) * arr->size * 2);
            arr->size = 0;
            arr->i = 0;
            return;
        }
        arr->size *= 2;
    }

    switch(type) {
        case INT:
            ((int*) arr->data)[arr->i++] = *((int*) el);
            return (int*) arr->data + arr->i;
        case INT32:
            ((int32_t*) arr->data)[arr->i++] = *((int32_t*) el);
            return (int32_t*) arr->data + arr->i;
        case UINT32:
            ((uint32_t*) arr->data)[arr->i++] = *((uint32_t*) el);
            return (uint32_t*) arr->data + arr->i;
        case INT64:
            ((int64_t*) arr->data)[arr->i++] = *((int64_t*) el);
            return (int64_t*) arr->data + arr->i;
        case UINT64:
            ((uint64_t*) arr->data)[arr->i++] = *((uint64_t*) el);
            return (uint64_t*) arr->data + arr->i;
        case FLOAT:
            ((float*) arr->data)[arr->i++] = *((float*) el);
            return (float*) arr->data + arr->i;
        case DOUBLE:
            ((double*) arr->data)[arr->i++] = *((double*) el);
            return (double*) arr->data + arr->i;
        case POINTER:
            ((char**) arr->data)[arr->i++] = el;
            return (char**) arr->data + arr->i;
        default:
            fprintf(stderr, "%s is an unknown datatype.\n", type);
            break;
    }
}
dynamArr* createNewDynamArr(DataType type) {
    
}


uint32_t hashInt(int key, int m) {
    return hash(&key, sizeof(int), m);
}
uint32_t hash(char* key, int n, int m) {
    uint32_t keySum = 0; 
    for(int i = 0; i < n; i++) {
        keySum += (uint32_t) key[i];
    }

    return m * fmod((keySum * sqrt(5.0) - 1.0) / 2.0, 1.0);
}

HashTable* createHashTable(uint32_t minSize, DataType type) {
    HashTable* table = malloc(sizeof(HashTable));
    if(!table) {
        fprintf(stderr, "An error occured when allocating space for a new HashTable.\n");
        return 0;
    }

    uint32_t size = pow(2, ceil(log2(minSize)));

    table->table = calloc(size, sizeof(dynamArr*));
    if(!table->table) {
        fprintf(stderr, "An error occured when allocating space for a new HashTable of size %d, with an element size of %d bytes (%d bytes total).\n",
        size, sizeofType(type), size * sizeofType(type));
        free(table);

        return 0;
    }

    table->size = size;
    table->type = type;

    return table;
}

void* insert(HashTable* table, char* key, size_t keySize, void* el, DataType type) {
    if(type != table->type) {
        fprintf(stderr, "The specified datatype (%s) does not match the datatype of the specified HashTable (%s).", 
            type, table->type);
        return 0;
    }

    uint32_t hashKey = hash(key, keySize, table->size);
    dynamArr* chain = table->table[hashKey];
    if(!chain) {
        chain = createNewDynamArr(type);
        if(!chain) {
            fprintf(stderr, "A problem occured when allocating space for a new chain in the Hashtable.\n");
            return 0;
        }
        table->table[hashKey] = chain;
    }

    return insertInto()
}