//
// Created by R on 11/7/2024.
//

#ifndef UTIL_H
#define UTIL_H

typedef struct Pixel {
    int red;
    int green;
    int blue;
} Pixel;

typedef struct ArrayDouble {
    double *data;
    int size;
} ArrayDouble;

typedef struct ArrayPixel {
    Pixel *data;
    int size;
} ArrayPixel;

typedef struct Array2Ddouble {
    double **data;
    int height;
    int width;
} Array2Ddouble;

typedef struct Array2DPixel {
    Pixel **data;
    int height;
    int width;
} Array2DPixel;

typedef struct Matrix {
    Array2Ddouble array;
    char name[32];
} Matrix;

typedef struct Img {
    Array2DPixel array;
    int height;
    int width;
} Img;


char *strcopy(const char *orig);


#endif //UTIL_H
