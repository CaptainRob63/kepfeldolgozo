//
// Created by R on 11/7/2024.
//

#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>



typedef struct Pixel1Byte {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Pixel1Byte;

typedef struct Pixel2Byte {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
}Pixel2Byte;



typedef struct StringArray {
    char** data;
    int size;
} StringArray;

typedef enum IMAGE_TYPE {
    P1 = 1,
    P2 = 2,
    P3 = 3,
    P4 = 4,
    P5 = 5,
    P6 = 6,
} IMAGE_TYPE;


typedef struct Image {
    IMAGE_TYPE TYPE;
    uint16_t maxValue;
    StringArray comments;
    Pixel1Byte **array1;
    Pixel2Byte **array2;
    int height;
    int width;
} Image;



void img_free(Image img);



typedef struct ArrayDouble {
    double *data;
    int size;
} ArrayDouble;

typedef struct Array2Ddouble {
    double **data;
    int height;
    int width;
} Array2Ddouble;

typedef struct Matrix {
    Array2Ddouble array;
    char name[32];
} Matrix;


void string_array_print(StringArray *strArr, char *name);

void string_array_free(StringArray *strArr);

char *strcopy(const char *orig);


#endif //UTIL_H
