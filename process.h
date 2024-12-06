//
// Created by R on 12/6/2024.
//
#pragma once

#include "util.h"

#ifndef PROCESS_H
#define PROCESS_H


static double matrix_normalisation_constant(Matrix matrix);

static void process_pixel(Image *img, int x, int y, Matrix matrix, double norm, float max, float min);

static void sum_pixel(Image *img, int x, int y, Matrix matrix, double norm, double *red, double *green, double *blue);

static void img_max_min_value(Image *img, Matrix *matrix, double *maxOut, double *minOut);

void process_image(Image *img, Matrix matrix);


#endif //PROCESS_H
