#ifndef DATA_H
#define DATA_H

typedef enum DataType {
    CHAR,
    UCHAR,
    INT,
    INT32,
    UINT32,
    INT64,
    UINT64,
    FLOAT,
    DOUBLE,
    POINTER,
    STRING
} DataType;

unsigned char sizeOfType(DataType type);
char compare(void* el1, void* el2, DataType type);
void printType(void* el, DataType type);
void printTypeBlank(void* el, DataType type);

#endif