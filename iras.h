//
// Created by R on 11/2/2024.
//
#pragma once

#include <stdio.h>
#include "util.h"


#ifndef IRAS_H
#define IRAS_H


void write_matrix(const Matrix *matrix, FILE *fp);

void write_image_P6(const Image *img, FILE *fp);

#endif //IRAS_H
