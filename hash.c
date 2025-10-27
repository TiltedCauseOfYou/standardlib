#include "hash.h"

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
            fprintf(stderr, "Unknown datatype used.\n");
            return 0;
    }
}

uint8_t insertInto(dynamArr* arr, Data* data) {
    if(arr->size <= arr->i) {
        arr->data = realloc(arr->data, sizeof(Data*) * arr->size * 2);
        if(!arr->data) {
            fprintf(stderr, "An error occured when reallocating space for a HashTable of size %lu to size %lu.\n",
            arr->size, arr->size * 2);
            arr->size = 0;
            arr->i = 0;
            return 0;
        }
        arr->size *= 2;
    }
    arr->data[arr->i] = data;
    arr->i++;

    return 1;
}

dynamArr* createNewDynamArr() {
    dynamArr* arr = malloc(sizeof(dynamArr));
    if(!arr) {
        fprintf(stderr, "An error occured when allocating space for a new chain.\n");
        return 0;
    }
    arr->data = malloc(sizeof(Data*) * 4);
    if(!arr->data) {
        fprintf(stderr, "An error occured when allocating space for a new chain.\n");
        free(arr);
        return 0;
    }
    arr->size = 4;
    arr->i = 0;
    
    return arr;
}


uint32_t hash(char* key, size_t n, size_t m) {
    uint32_t keySum = 0; 
    for(size_t i = 0; i < n; i++) {
        keySum += (uint32_t) key[i];
    }

    double decimal = fmod((keySum * sqrt(5.0) - 1.0) / 2.0, 1.0);
    if(decimal < 0) decimal = - decimal;
    return m * decimal;
}

HashTable* createHashTable(uint32_t minSize) {
    HashTable* table = malloc(sizeof(HashTable));
    if(!table) {
        fprintf(stderr, "An error occured when allocating space for a new HashTable.\n");
        return 0;
    }

    uint32_t size = pow(2, ceil(log2(minSize)));

    table->table = calloc(size, sizeof(dynamArr*));
    if(!table->table) {
        fprintf(stderr, "An error occured when allocating space for a new HashTable of size %d.\n", size);
        free(table);

        return 0;
    }

    table->size = size;
    table->insertCount = 0;

    return table;
}

uint8_t insert(HashTable* table, char* key, size_t keySize, void* data, DataType type) {
    uint32_t hashKey = hash(key, keySize, table->size);
    dynamArr* chain = table->table[hashKey];
    if(!chain) {
        chain = createNewDynamArr();
        if(!chain) {
            fprintf(stderr, "A problem occured when allocating space for a new chain in the Hashtable.\n");
            return 0;
        }
        table->table[hashKey] = chain;
    }

    Data* node = malloc(sizeof(Data));
    if(!node) {
        fprintf(stderr, "An error occured when allocating space for a new element.\n");
        return 0;
    }

    node->data = data;
    node->key = key;
    node->keySize = keySize;
    node->type = type;

    table->insertCount++;

    return insertInto(chain, node);
}

void printTable(HashTable* table) {
    for(size_t i = 0; i < table->size; i++) {
        printf("Bucket %lu:\n", i);
        dynamArr* arr = table->table[i];
        if(arr) {
            for(size_t j = 0; j < arr->i; j++) {
                Data* data = arr->data[j];
                printf("%d\n", *((int*) data->data));
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

void freeNode(Data* data) {
    if(data) {
        if(data->data)
            free(data->data);
        free(data);
    }
}

void freeChain(dynamArr* chain) {
    if(chain) {
        for(size_t i = 0; i < chain->i; i++) {
            if(chain->data[i])
                freeNode(chain->data[i]);
        }
        free(chain);
    }
}

void freeTable(HashTable* table) {
    if(table) {
        for(size_t i = 0; i < table->size; i++) {
            freeChain(table->table[i]);
        }
    }
    free(table);
}