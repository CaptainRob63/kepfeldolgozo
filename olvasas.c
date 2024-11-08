//
// Created by R on 11/2/2024.
//

#include "olvasas.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG

#ifdef DEBUG
#define SHOW printf
#else
#define SHOW // macros
#endif



// Initializes a matrix. Arguments are just argv[].
// Data is copied to matrix with a buffer string that is tokenized.

// Inicializál egy mátrix struktúrát. Argumentumai stringek, így argv[] elemei egyszerűen átadhatók neki.
// Data először egy bufferbe másolva stringként, majd tokenizálással olvasva doubleként.

Matrix read_matrix(const char *name, const char *height, const char *width,  const char *data) {
    Matrix matrix;

    for (int i = 0; i < 32; i++)
        matrix.name[i] = '\0';

    for (int i = 0; name[i] != '\0'; i++) {
        matrix.name[i] = name[i];
        SHOW("copied 1 char to matrix name\n");
    }


    matrix.array.height = atof(height);
    matrix.array.width = atof(width);
    SHOW("set matrix height and width\n");


    matrix.array.data = (double**) malloc(matrix.array.height * sizeof(double));
    matrix.array.data[0] = (double*) malloc(matrix.array.width * matrix.array.height * sizeof(double));

    for (int i = 0; i < matrix.array.height; i++)
        matrix.array.data[i] = matrix.array.data[0] + i * matrix.array.width;


    char *databuffer = strcopy(data);
    char *tok = strtok(databuffer, " ");
    SHOW("token : %s\n", tok);

    for (int i = 0; i < matrix.array.height; i++) {
        for (int j = 0; j <matrix.array.width; j++) {
            matrix.array.data[i][j] = atof(tok);
            tok = strtok(NULL, " ");
        }
    }
    free(databuffer);

    return matrix;
}


Pixel1Byte read_pixel1Byte(char r, char g, char b) {
    Pixel1Byte pixel;

    pixel.red = r;
    pixel.green = g;
    pixel.blue = b;

    return pixel;
}

Pixel2Byte read_pixel2Byte(unsigned short r, unsigned short g, unsigned short b) {
    Pixel2Byte pixel;

    pixel.red = r;
    pixel.green = g;
    pixel.blue = b;

    return pixel;
}