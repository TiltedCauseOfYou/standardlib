#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

typedef struct vec32 {
    uint32_t* arr;
    uint32_t size;
    uint32_t i;
} vec32;

void appendA(vec32* vec, uint32_t el, float a) {
    if(vec->i >= vec->size) {
        printf("Next size: %d\n", (int) (4.0 * a * vec->size));
        vec->arr = realloc(vec->arr, a * 4.0 * vec->size);
        if(!vec->arr) {
            fprintf(stderr, "An error occured reallocating space for a vector size %d.\n", vec->size);
            vec->size = 0;
            vec->i = 0;
            vec->arr = 0;

            return;
        }
        memset(vec->arr + vec->i, 0, a * 2.0 * vec->size);
        vec->size *= a;
    }

    vec->arr[vec->i++] = el; 
}
void append(vec32* vec, uint32_t el) {
    appendA(vec, el, 2.0);
}

uint32_t popA(vec32* vec, float a) {
    if(!vec->i) {
        fprintf(stderr, "IndexOutOfBoundsError: You can not pop an empty vector.\n");
        return 0;
    }
    uint32_t data = vec->arr[vec->i--]; 

    if(vec->i <= vec->size * a && vec->size > 16) {
        int size = 16;
        if(vec->size * a > 16) size = vec->size * a;
        else return data;
        vec->arr = realloc(vec->arr, size * 4 * a);
        if(!vec->arr) {
            fprintf(stderr, "An error occured reallocating space for a vector size %d / %d.\n", vec->size, size);
            vec->size = 0;
            vec->arr = 0;
            vec->i = 0;

            return 0;
        }
        vec->size = size;
    }

    return data;
}
uint32_t pop(vec32* vec) {
    return popA(vec, 0.25);
}

vec32* newVecA(uint32_t a) {
    vec32* vec = malloc(sizeof(vec32));
    if(!vec) {
        fprintf(stderr, "An error occured when allocating space for a new vector of size %d.\n", a);
        return 0;
    }

    vec->arr = calloc(a, 4);
    if(!vec->arr) {
        fprintf(stderr, "An error occured when allocating space for a new vector of size %d.\n", a);
        free(vec);
        return 0;
    }

    vec->i = 0;
    vec->size = a;
    
    return vec;
}
vec32* newVec() {
    return newVecA(16);
}

uint32_t get(vec32* vec, uint32_t i) {
    if(i < 0 || i >= vec->size) {
        fprintf(stderr, "IndexOutOfBoundError: Index %d out of bounds for vector of size %d.\n", i, vec->size);
        return 0;
    }
    return vec->arr[i];
}
void set(vec32* vec, uint32_t i, uint32_t el) {
    if(i < 0 || i >= vec->size) {
        fprintf(stderr, "IndexOutOfBoundError: Index %d out of bounds for vector of size %d.\n", i, vec->size);
        return;
    }
    if(i >= vec->i) vec->i = i + 1;
    vec->arr[i] = el;
}

void printVecFull(vec32* vec) {
    uint32_t i = vec->i;
    vec->i = vec->size;
    printVec(vec);
    vec->i = i;
}
void printVec(vec32* vec) {
    uint32_t size = vec->i;
    printf("<[");
    if(size > 0) {
        for(int i = 0; i < size - 1; i++) printf("%d, ", vec->arr[i]);
        printf("%d]>\n", vec->arr[size-1]);
    } else printf("]>\n");
}

void freeVec(vec32* vec) {
    if(vec) {
        if(vec->arr) free(vec->arr);
        free(vec);
    }
}