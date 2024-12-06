//
// Created by R on 12/6/2024.
//
#include "process.h"
#include <stdlib.h>
#include "util.h"

static double matrix_normalisation_constant(Matrix matrix) {
    double acc = 0;
    for (int i = 0; i < matrix.array.height; ++i) {
        for (int j = 0; j < matrix.array.width; ++j) {
            acc += matrix.array.data[i][j];
        }
    }

    // holy ward spell against magic numbers
    float EPSILON = 0.1;
    if (abs(acc) < EPSILON) // if (acc == 0)
        return 1;

    return acc;
}

static void process_pixel(Image *img, int x, int y, Matrix matrix, double norm, float max, float min) {
    double accR = 0;
    double accG = 0;
    double accB = 0;

    int startPosX = x - (matrix.array.width  - 1) / 2;
    int startPosY = y - (matrix.array.height - 1) / 2;

    for (int i = 0; i < matrix.array.height; ++i) {
        for (int j = 0; j < matrix.array.width; ++j) {

            if (startPosX + j  <  0            |
                startPosX + j  >=  img->width  |
                startPosY + i  <  0            |
                startPosY + i  >=  img->height )

                {
                norm -= matrix.array.data[i][j];
                continue;
            }

            if (img->array1 != NULL) {
                accR += matrix.array.data[i][j] * img->array1 [startPosY + i]  [startPosX + j].red;
                accG += matrix.array.data[i][j] * img->array1 [startPosY + i]  [startPosX + j].green;
                accB += matrix.array.data[i][j] * img->array1 [startPosY + i]  [startPosX + j].blue;
            }

            if (img->array2 != NULL) {
                accR += matrix.array.data[i][j] * img->array2 [startPosY + i]  [startPosX + j].red;
                accG += matrix.array.data[i][j] * img->array2 [startPosY + i]  [startPosX + j].green;
                accB += matrix.array.data[i][j] * img->array2 [startPosY + i]  [startPosX + j].blue;
            }

        }
    }

    if (img->array1 != NULL) {
        img->array1[y][x].red   =  (accR / norm - min) / (max - min) * 255;
        img->array1[y][x].green =  (accG / norm - min) / (max - min) * 255;
        img->array1[y][x].blue  =  (accB / norm - min) / (max - min) * 255;
    }

    if (img->array2 != NULL) {
        img->array2[y][x].red   =  (accR / norm - min) / (max - min) * 65535;
        img->array2[y][x].green =  (accG / norm - min) / (max - min) * 65535;
        img->array2[y][x].blue  =  (accB / norm - min) / (max - min) * 65535;
    }

}

static void sum_pixel(Image *img, int x, int y, Matrix matrix, double norm, double *red, double *green, double *blue) {
    double accR = 0;
    double accG = 0;
    double accB = 0;

    int startPosX = x - (matrix.array.width  - 1) / 2;
    int startPosY = y - (matrix.array.height - 1) / 2;

    for (int i = 0; i < matrix.array.height; ++i) {
        for (int j = 0; j < matrix.array.width; ++j) {

            if (startPosX + j  <  0            |
                startPosX + j  >=  img->width  |
                startPosY + i  <  0            |
                startPosY + i  >=  img->height )

            {
                norm -= matrix.array.data[i][j];
                continue;
            }


            accR += matrix.array.data[i][j] * img->array1 [startPosY + i]  [startPosX + j].red;
            accG += matrix.array.data[i][j] * img->array1 [startPosY + i]  [startPosX + j].green;
            accB += matrix.array.data[i][j] * img->array1 [startPosY + i]  [startPosX + j].blue;

        }
    }

    *red   =  accR / norm;
    *green =  accG / norm;
    *blue  =  accB / norm;
}

static void img_max_min_value(Image *img, Matrix *matrix, double *maxOut, double *minOut) {
    double min = 0, max = 0;
    double red, green, blue;
    double norm = matrix_normalisation_constant(*matrix);
    for (int i = 0; i < img->height; ++i)
        for (int j = 0; j < img->width; ++j) {
            sum_pixel(img, j, i, *matrix, norm, &red, &green, &blue);
            if (red < min)   min = red;
            if (green < min) min = green;
            if (blue < min)  min = blue;

            if (red > max)   max = red;
            if (green > max) max = green;
            if (blue > max)  max = blue;
        }

    *maxOut = max;
    *minOut = min;
}

void process_image(Image *img, Matrix matrix) {
    double norm = matrix_normalisation_constant(matrix);
    double max, min;
    img_max_min_value(img, &matrix, &max, &min);

    for (int i = 0; i < img->height; ++i)
        for (int j = 0; j < img->width; ++j)
            process_pixel(img, j, i, matrix, norm, max, min);

}


