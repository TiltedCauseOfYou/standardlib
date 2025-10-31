#include "hash.h"

const uint32_t FNV_offset_basis = 0x811c9dc5;
const uint32_t FNV_prime = 0x01000193;


unsigned char hash_switch = 0;

void incHashSwitch() {
    hash_switch++;
}

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

void freeTableRealloc(HashTable* table);
unsigned char inTable(HashTable* table, char* key, size_t keySize);

double log_base(double base, double x) {
    return log10(x) / log10(base);
}

uint32_t mul_hash(char* key, size_t n, size_t m) {
    uint32_t keySum = 0;
    for(size_t i = 0; i < n; i++) {
        keySum += key[i];
    }

    double decimal = keySum * ((sqrt(5.0) - 1.0) / 2.0);
    if(decimal < 0) decimal = -decimal;
    decimal = decimal - floor(decimal);

    return floor(m * decimal);
}

uint32_t fnv_hash(char* key, size_t n, size_t m) {
    uint32_t hash = FNV_offset_basis;
    for(size_t i = 0; i < n; i++) {
        hash ^= key[i];
        hash *= FNV_prime;
    }

    return hash % m;
}

uint32_t djb2_hash(char* key, size_t n, size_t m) {
    uint32_t hash = 5381;

    for(size_t i = 0; i < n; i++) {
        hash = hash * 33 ^ key[i];
    }
    return hash % m;
}

uint32_t sdbm_hash(char* key, size_t n, size_t m) {
    uint32_t hash = 0;
    for(size_t i = 0; i < n; i++) {
        hash = key[i] + (hash << 6) + (hash << 16) - hash;
    }
    return hash % m;
}

uint32_t joaat_hash(char* key, size_t n, size_t m) {
    uint32_t hash = 0;
    for(size_t i = 0; i < n; i++) {
        hash += key[i];
        hash += hash << 10;
        hash ^= hash >> 6;
    }

    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;

    return hash % m;
}

uint32_t hash(char* key, size_t n, size_t m) {
    switch(hash_switch) {
        case 0:
            return mul_hash(key, n, m);
        case 1:
            return fnv_hash(key, n, m);
        case 2:
            return djb2_hash(key, n, m);
        case 3:
            return sdbm_hash(key, n, m);
        case 4:
            return joaat_hash(key, n, m);
        default:
            fprintf(stderr, "Unknown hash_switch value.\n");
            return fnv_hash(key, n, m);
    }
}

HashTable* createHashTable(uint32_t minSize) {
    HashTable* table = malloc(sizeof(HashTable));
    if(!table) {
        fprintf(stderr, "An error occured when allocating space for a new HashTable.\n");
        return 0;
    }

    uint32_t size = 11;
    while(size < minSize) size *= 2;

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
    if(inTable(table, key, keySize)) {
        Data* el = get(table, key, keySize);
        el->data = data;
        return 1;
    }
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

    if(((double) table->insertCount) / table->size >= 0.75) {
        HashTable* newTable = createHashTable(table->size * 2);
        if(!newTable) {
            fprintf(stderr, "An error occured when allocating space for a bigger Hash Table.\n");
            return 0;
        }
        
        for(size_t i = 0; i < table->size; i++) {
            LinkedList* list = table->table[i];
            if(list) {
                ListNode* cur = list->head;
                while(cur) {
                    Data* node = (Data*) cur->data;
                    if(node) {
                        //TODO: free newTable if insert fails
                        insert(newTable, node->key, node->keySize, node->keyType, node->data, node->type);
                        free(node);
                    }
                    ListNode* next = cur->next;
                    free(cur);
                    cur = next;
                }
                free(list);
            }
        }
        free(table->table);

        table->table = newTable->table;
        table->size *= 2;

        free(newTable);

        hashKey = hash(key, keySize, table->size);
        chain = table->table[hashKey];
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
    unsigned char ret = insertIntoList(chain, node, POINTER);

    return ret;
}

unsigned char compareKey(void* e1, void* e2) {
    Data* el1 = (Data*) e1;
    Data* el2 = (Data*) e2;

    if(el1->keySize != el2->keySize) return 0;
    if(!strncmp((char*) el1->key, (char*) el2->key, el1->keySize))
        return 1;
    return 0;
}

void* delete(HashTable* table, char* key, size_t keySize) {
    if(!inTable(table, key, keySize)) return 0;

    Data* comp = malloc(sizeof(Data*));
    if(!comp) {
        fprintf(stderr, "An error occured when allocating space for a temporary element.\n");
        return 0;
    }

    uint32_t hashKey = hash(key, keySize, table->size);
    LinkedList* chain = table->table[hashKey];
    if(!chain) {
        free(comp);
        return 0;
    }
    if(table->insertCount * 0.25 <= table->size) {
        HashTable* newTable = createHashTable(table->size / 2);
        if(!newTable){
            fprintf(stderr, "An error occured when allocating space for a bigger Hash Table.\n");
            free(comp);
            return 0;
        }
        
        for(size_t i = 0; i < table->size; i++) {
            LinkedList* list = table->table[i];
            if(list) {
                ListNode* cur = list->head;
                while(cur) {
                    Data* el = (Data*) cur->data;
                    insert(newTable, el->key, el->keySize, el->keyType, el->data, el->type);
                    ListNode* next = cur->next;
                    free(cur);
                    cur = next;
                }
                free(list);
            }
        }
        free(table->table);

        table->table = newTable->table;
        table->size /= 2;

        free(newTable);

        hashKey = hash(key, keySize, table->size);
        chain = table->table[hashKey];
    }

    table->insertCount--;
    Data* node = find(chain, comp, &compareKey);
    free(comp);

    void* ret = ((Data*) deleteFromList(chain, node, POINTER))->data;
    free(node);
    return ret;
}

unsigned char inTable(HashTable* table, char* key, size_t keySize) {
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

    char exist = exists(chain, data, &compareKey);
    free(data);
    return exist;
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

Data** getAll(HashTable* table) {
    Data** all = malloc(sizeof(Data*) * table->insertCount + 1);
    if(!all) {
        fprintf(stderr, "An error occurred when allocating space for the return array.\n");
        return 0;
    }
    all[table->insertCount] = 0;
    size_t p = 0;
    for(size_t i = 0; i < table->size; i++) {
        LinkedList* list = table->table[i];
        if(list) {
            ListNode* cur = list->head;
            while(cur) {
                all[p++] = (Data*) cur->data;
                cur = cur->next;
            }
        }
    }

    return all;
}

Key** getAllKeys(HashTable* table) {
    Key** keys = malloc(sizeof(Key*) * table->insertCount + 1);
    if(!keys) {
        fprintf(stderr, "An error occurred when allocating space for the return array.\n");
        return 0;
    }
    keys[table->insertCount] = 0;
    size_t p = 0;
    for(size_t i = 0; i < table->size; i++) {
        LinkedList* list = table->table[i];
        if(list) {
            ListNode* cur = list->head;
            while(cur) {
                Key* key = malloc(sizeof(Key));
                if(!key) {
                    fprintf(stderr, "An error occurred when allocating space for a key object.\n");
                    for(size_t j = 0; j < p; j++) {
                        free(keys[j]);
                    }
                    free(keys);
                    return 0;
                }
                Data* data = cur->data;
                key->key = data->key;
                key->keySize = data->keySize;
                key->type = data->keyType;
                keys[p++] = key;
                cur = cur->next;
            }
        }
    }

    return keys;
}

size_t countCollisions(LinkedList* chain) {
    if(!chain || !chain->head) return 0;
    size_t collisions = 0;

    ListNode* cur = chain->head->next;
    while(cur) {
        collisions++;
        cur = cur->next;
    }

    return collisions;
}

size_t countTotalCollisions(HashTable* table) {
    size_t collisions = 0;
    for(size_t i = 0; i < table->size; i++) {
        collisions += countCollisions(table->table[i]);
    }
    return collisions;
}

void printNode(void* node) {
    if(node)
        printTypeBlank(((Data*) node)->data, ((Data*) node)->type);
}

void printBuckets(HashTable* table) {
    size_t size = table->size;
    size_t collissions = 0;
    for(size_t i = 0; i < size; i++) {
        printf("Bucket %lu:\n", i);
        printLinkedListCustom(table->table[i], &printNode);
        collissions += countCollisions(table->table[i]);
    }
    printf("\nCollision: %lu (%.02lf%%)\n\n", collissions, (((double) collissions / table->insertCount)) * 100);
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

void freeNode(void* node) {
    if(node) {
        if(((Data*) node)->data)
            free(((Data*) node)->data);
        if(((Data*) node)->key && ((Data*) node)->data != ((Data*) node)->key)
            free(((Data*) node)->key);
        free(node);
    }
}

void freeTableRealloc(HashTable* table) {
    if(table) {
        for(size_t i = 0; i < table->size; i++) {
            freeList(table->table[i]);
        }
        free(table->table);
        free(table);
    }
}

void freeTable(HashTable* table) {
    if(table) {
        for(size_t i = 0; i < table->size; i++) {
            freeListCustom(table->table[i], &freeNode);
        }
        free(table->table);
        free(table);
    }
}