//
// Created by R on 11/2/2024.
//
#pragma once

#include <stdio.h>
#include "util.h"


#ifndef IRAS_H
#define IRAS_H


void write_matrix(const Matrix *matrix, FILE *fp);

void write_image(Image *image);

#endif //IRAS_H
