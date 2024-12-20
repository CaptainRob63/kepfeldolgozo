//
// Created by R on 11/7/2024.
//

#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


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
    char* name;
    uint16_t maxValue;
    StringArray comments;
    Pixel1Byte **array1;
    Pixel2Byte **array2;
    int height;
    int width;
} Image;


typedef struct ArrayDouble {
    double *data;
    int size;
} ArrayDouble;

typedef struct Array2Ddouble {
    double **data;
    unsigned int height;
    unsigned int width;
} Array2Ddouble;

typedef struct Matrix {
    Array2Ddouble array;
    char name[32];
} Matrix;

typedef enum MATRIX_ERROR {
    MATERR_NONE,
    MATERR_NAME,
    MATERR_WIDTH,
    MATERR_HEIGHT,
    MATERR_ARRAY
} MATRIX_ERROR;

void str_newline_to_zero(char *str);

void string_array_print(StringArray *strArr, char *name);

void string_array_free(StringArray *strArr);

// basic string copier. Returns mallocated string. Caller must free. returns NULL if failed.
// alap string másoló. Visszatér egy dinamikusan allokált stringgel. Hívónak felelőssége felszabadítani. NULL pointerrel tér vissza ha sikertelen a foglalás.
char *strcopy(const char *orig);

void image_free(Image *img);

void matrix_free(Matrix *matrix);

int8_t matrix_find_in_file(const char *name, FILE *fp);

MATRIX_ERROR matrix_check_error(Matrix matrix);

void matrix_write_error(MATRIX_ERROR Error);


#endif //UTIL_H
