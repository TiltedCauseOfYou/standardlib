#include <stdint.h>

#ifndef VECTOR_H
#define VECTOR_H

struct vec32;
typedef vec32 vec32;

void append(vec32* vec, uint32_t el);
void appendA(vec32* vec, uint32_t el, float a);

void pop(vec32* vec);
void popA(vec32* vec, float a);

vec32* newVec();
vec32* newVecA(int a);

uint32_t get(vec32* vec, uint32_t i);
void set(vec32* vec, uint32_t i, uint32_t el);

#endif VECTOR_H