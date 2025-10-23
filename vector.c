#include <errno.h>

#include "vector.h"

struct vec32 {
    uint32_t* arr;
    uint32_t size;
    uint32_t i;
};

void append(vec32* vec, uint32_t el) {
    if(vec->i >= vec->size) {
        vec->arr = realloc(vec->arr, 8 * vec->size);
        if(!vec->arr) {
            perror("An error occured reallocating space for a vector size %d.\n", vec->size);
            vec->size = 0;
            vec->i = 0;

            return;
        }
        memset(vec->arr + vec->i, 0, 4 * vec->size);
        vec->size *= 2;
    }

    vec->arr[vec->i++] = el; 
}
void appendA(vec32* vec, uint32_t el, float a) {
    if(vec->i >= vec->size) {
        vec->arr = realloc(vec->arr, a * 4.0 * vec->size);
        if(!vec->arr) {
            perror("An error occured reallocating space for a vector size %d.\n", vec->size);
            vec->size = 0;
            vec->i = 0;

            return;
        }
        memset(vec->arr + vec->i, 0, a * 3.0 * vec->size);
        vec->size *= a;
    }

    vec->arr[vec->i++] = el; 
}

void pop(vec32* vec) {
    if(!vec->i) {
        perror("IndexOutOfBoundsError: You can not pop an empty vector.\n");
        return;
    }
    vec->arr[vec->i--]; 

    if(vec->i <= vec->size * 0.25) {
        vec->arr = realloc(vec->arr, 0.25 * vec->size);
        if(!vec->arr) {
            perror("An error occured reallocating space for a vector size %d.\n", vec->size);
            vec->size = 0;
            vec->i = 0;

            return;
        }
        vec->size *= 0.25;
    }
}
void popA(vec32* vec, float a) {
    if(!vec->i) {
        perror("IndexOutOfBoundsError: You can not pop an empty vector.\n");
        return;
    }
    vec->arr[vec->i--]; 

    if(vec->i <= vec->size * a) {
        vec->arr = realloc(vec->arr, a * vec->size);
        if(!vec->arr) {
            perror("An error occured reallocating space for a vector size %d.\n", vec->size);
            vec->size = 0;
            vec->i = 0;

            return;
        }
        vec->size *= a;
    }
}

vec32* newVec() {
    vec32* vec = malloc(sizeof(vec32));
    if(!vec) {
        perror("An error occured when allocating space for a new vector.");
        return 0;
    }

    vec->arr = calloc(4 * 16);
    if(!vec->arr) {
        perror("An error occured when allocating space for a new vector.");
        free(vec);
        return 0;
    }

    vec->i = 0;
    vec->size = 0;
}
vec32* newVecA(int a) {
    vec32* vec = malloc(sizeof(vec32));
    if(!vec) {
        perror("An error occured when allocating space for a new vector of size %d.", a);
        return 0;
    }

    vec->arr = calloc(4 * a);
    if(!vec->arr) {
        perror("An error occured when allocating space for a new vector of size %d.", a);
        free(vec);
        return 0;
    }

    vec->i = 0;
    vec->size = 0;
}

uint32_t get(vec32* vec, uint32_t i) {
    if(i < 0 || i >= vec->size) {
        perror("IndexOutOfBoundError: Index %d out of bounds for vector of size %d.", i, vec->size);
        return;
    }
    return vec->arr[i];
}
void set(vec32* vec, uint32_t i, uint32_t el) {
    if(i < 0 || i >= vec->size) {
        perror("IndexOutOfBoundError: Index %d out of bounds for vector of size %d.", i, vec->size);
        return;
    }
    if(i >= vec->i) vec->i = i + 1;
    vec->arr[i] = el;
}