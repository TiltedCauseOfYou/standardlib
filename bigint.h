#include "vector"

#ifndef BIGINT_H
#define BIGINT_H

struct big_int;
typedef struct big_int big_int;

void add(big_int* b, int i);
void addBig(big_int* b1, big_int* b2);

void sub(big_int* b, int i);
void subBig(big_int* b1, big_int* b2);

void mul(big_int* b, int i);
void mulBig(big_int* b1, big_int* b2);

void div(big_int* b, int i);
void divBig(big_int* b1, big_int* b2);

big_int* newBigInt(int i);

#endif BIGINT_H