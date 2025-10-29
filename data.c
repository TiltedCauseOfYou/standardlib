#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "data.h"

unsigned char sizeOfType(DataType type) {
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

char compare(void* el1, void* el2, DataType type) {
    switch(type) {
        case CHAR:
            if(*((char*) el1) == *((char*) el2)) return 0;
            if(*((char*) el1) > *((char*) el2)) return 1;
            return -1;
        case UCHAR:
            if(*((unsigned char*) el1) == *((unsigned char*) el2)) return 0;
            if(*((unsigned char*) el1) > *((unsigned char*) el2)) return 1;
            return -1;
        case INT:
            if(*((int*) el1) == *((int*) el2)) return 0;
            if(*((int*) el1) > *((int*) el2)) return 1;
            return -1;
        case INT32:
            if(*((int32_t*) el1) == *((int32_t*) el2)) return 0;
            if(*((int32_t*) el1) > *((int32_t*) el2)) return 1;
            return -1;
        case UINT32:
            if(*((uint32_t*) el1) == *((uint32_t*) el2)) return 0;
            if(*((uint32_t*) el1) > *((uint32_t*) el2)) return 1;
            return -1;
        case INT64:
            if(*((int64_t*) el1) == *((int64_t*) el2)) return 0;
            if(*((int64_t*) el1) > *((int64_t*) el2)) return 1;
            return -1;
        case UINT64:
            if(*((uint64_t*) el1) == *((uint64_t*) el2)) return 0;
            if(*((uint64_t*) el1) > *((uint64_t*) el2)) return 1;
            return -1;
        case FLOAT:
            if(*((float*) el1) == *((float*) el2)) return 0;
            if(*((float*) el1) > *((float*) el2)) return 1;
            return -1;
        case DOUBLE:
            if(*((double*) el1) == *((double*) el2)) return 0;
            if(*((double*) el1) > *((double*) el2)) return 1;
            return -1;
        case POINTER:
            if(el1 == el2) return 0;
            return 1;
        case STRING:
            return strcmp((char*) el1, (char*) el2);
        default:
            fprintf(stderr, "Unknown datatype given.\n");
            return 0;
    }
}

void printType(void* el, DataType type) {
    if(!el) return;
    switch(type) {
        case INT:
            printf("%-10d", *((int*) el));
            break;
        case INT32:
            printf("%-10d", *((int32_t*) el));
            break;
        case UINT32:
            printf("%-10u", *((uint32_t*) el));
            break;
        case INT64:
            printf("%-10ld", *((int64_t*) el));
            break;
        case UINT64:
            printf("%-10lu", *((uint64_t*) el));
            break;
        case FLOAT:
            printf("%-10f", *((float*) el));
            break;
        case DOUBLE:
            printf("%-10lf", *((double*) el));
            break;
        case POINTER:
            printf("%-10p", el);
            break;
        default:
            fprintf(stderr, "Unknown datatype.\n");
    }
}

void printTypeBlank(void* el, DataType type) {
    if(!el) return;
    switch(type) {
        case INT:
            printf("%d", *((int*) el));
            break;
        case INT32:
            printf("%d", *((int32_t*) el));
            break;
        case UINT32:
            printf("%u", *((uint32_t*) el));
            break;
        case INT64:
            printf("%ld", *((int64_t*) el));
            break;
        case UINT64:
            printf("%lu", *((uint64_t*) el));
            break;
        case FLOAT:
            printf("%f", *((float*) el));
            break;
        case DOUBLE:
            printf("%lf", *((double*) el));
            break;
        case POINTER:
            printf("%p", el);
            break;
        default:
            fprintf(stderr, "Unknown datatype.\n");
    }
}