#include <stdint.h>
#include <stdio.h>

#ifndef VECTOR_H
#define VECTOR_H

typedef struct vec32 vec32;

void append(vec32* vec, uint32_t el);
void appendA(vec32* vec, uint32_t el, float a);

void pop(vec32* vec);
void popA(vec32* vec, float a);

vec32* newVec();
vec32* newVecA(uint32_t a);

uint32_t get(vec32* vec, uint32_t i);
void set(vec32* vec, uint32_t i, uint32_t el);

void printVec(vec32* vec);
void freeVec(vec32* vec);

#endif VECTOR_H