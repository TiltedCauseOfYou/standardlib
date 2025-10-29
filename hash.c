#include "hash.h"


/* uint8_t insertInto(dynamArr* arr, Data* data) {
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

void* getFrom(dynamArr* chain, char* key, size_t keySize) {
    if(!chain) return 0;

    for(size_t i = 0; i < chain->i; i++) {
        Data* data = chain->data[i];
        if(data->keySize == keySize && !strncmp(key, data->key, keySize)) return data->data;
    }
    return 0;
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
} */


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

    table->table = calloc(size, sizeof(LinkedList*));
    if(!table->table) {
        fprintf(stderr, "An error occured when allocating space for a new HashTable of size %d.\n", size);
        free(table);

        return 0;
    }

    table->size = size;
    table->insertCount = 0;

    return table;
}

uint8_t insert(HashTable* table, char* key, size_t keySize, DataType keyType, void* data, DataType type) {
    uint32_t hashKey = hash(key, keySize, table->size);
    LinkedList* chain = table->table[hashKey];
    if(!chain) {
        chain = createList();
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
    node->keyType = keyType;
    node->type = type;

    table->insertCount++;

    return insertIntoList(chain, node, POINTER);
}

unsigned char compareKey(void* e1, void* e2) {
    Data* el1 = (Data*) e1;
    Data* el2 = (Data*) e2;

    if(el1->keySize != el2->keySize) return 0;
    if(!strncmp((char*) el1->key, (char*) el2->key, el1->keySize))
        return 1;
    return 0;
}
void* get(HashTable* table, char* key, size_t keySize) {
    if(!table) {
        fprintf(stderr, "Cannot access table from Nullpointer.\n");
        return 0;
    }

    uint32_t hashKey = hash(key, keySize, table->size);
    LinkedList* chain = table->table[hashKey];
    Data* data = malloc(sizeof(Data));
    if(!data) {
        fprintf(stderr, "A proplem occurred when allocating space to search a chain in a Hash Table.\n");
        return 0;
    }
    data->key = key;
    data->keySize = keySize;

    void* el = find(chain, data, &compareKey);
    free(data);
    return el;
}

void printNode(void* node) {
    if(node)
        printTypeBlank(((Data*) node)->data, ((Data*) node)->type);
}

void printBuckets(HashTable* table) {
    size_t size = table->size;
    for(size_t i = 0; i < size; i++) {
        printf("Bucket %lu:\n", i);
        printLinkedListCustom(table->table[i], &printNode);
    }
}

void printTable(HashTable* table) {
    size_t size = table->insertCount;
    for(size_t i = 0; i < size; i++) {
        printf("+------------");
    }
    printf("+\n");
    for(size_t i = 0; i < table->size; i++) {
        LinkedList* list = table->table[i];
        if(list) {
            ListNode* cur = list->head;
            while(cur) {
                Data* data = (Data*) cur->data;
                printf("| ");
                printType(data->key, data->keyType);
                printf(" ");
                cur = cur->next;
            }
        }
    }
    printf("|\n");
    for(size_t i = 0; i < size; i++) {
        printf("+------------");
    }
    printf("+\n");
    for(size_t i = 0; i < table->size; i++) {
        LinkedList* list = table->table[i];
        if(list) {
            ListNode* cur = list->head;
            while(cur) {
                Data* data = (Data*) cur->data;
                printf("| ");
                printType(data->data, data->type);
                printf(" ");
                cur = cur->next;
            }
        }
    }
    printf("|\n\n");
}

void freeNode(void* data) {
    if(data) {
        if(((Data*) data)->data)
            free(((Data*) data)->data);
        free(data);
    }
}

void freeTable(HashTable* table) {
    if(table) {
        for(size_t i = 0; i < table->size; i++) {
            freeListCustom(table->table[i], &freeNode);
        }
    }
    free(table->table);
    free(table);
}