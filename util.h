//
// Created by R on 11/7/2024.
//

#ifndef UTIL_H
#define UTIL_H


typedef struct Pixel1Byte {
    char red;
    char green;
    char blue;
} Pixel1Byte;

typedef struct Pixel2Byte {
    unsigned short red;
    unsigned short green;
    unsigned short blue;
}Pixel2Byte;



typedef struct ArrayPixel1Byte {
    Pixel1Byte *data;
    int size;
} ArrayPixel1Byte;

typedef struct ArrayPixel2Byte {
    Pixel2Byte *data;
    int size;
} ArrayPixel2Byte;



typedef struct Array2DPixel1Byte {
    Pixel1Byte **data;
    int height;
    int width;
} Array2DPixel1Byte;

typedef struct Array2DPixel2Byte {
    Pixel2Byte **data;
    int height;
    int width;
} Array2DPixel2Byte;



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

typedef struct Img1Byte {
    IMAGE_TYPE TYPE;
    unsigned short maxValue;
    StringArray comments;
    Array2DPixel1Byte array;
    int height;
    int width;
} Img1Byte;

typedef struct Img2Byte {
    IMAGE_TYPE TYPE;
    unsigned short maxValue;
    StringArray comments;
    Array2DPixel2Byte array;
    int height;
    int width;
} Img2Byte;

void img1B_free(Img1Byte *img);
void img2B_free(Img2Byte * img);




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
