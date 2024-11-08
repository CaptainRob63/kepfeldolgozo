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



typedef struct Img1Byte {
    Array2DPixel2Byte array;
    int height;
    int width;
} Img1Byte;

typedef struct Img2Byte {
    Array2DPixel2Byte array;
    int height;
    int width;
} Img2Byte;





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

char *strcopy(const char *orig);


#endif //UTIL_H
