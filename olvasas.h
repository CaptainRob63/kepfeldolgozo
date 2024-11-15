//
// Created by R on 11/2/2024.
//
#pragma once

#include <stdio.h>
#include "util.h"

#ifndef OLVASAS_H
#define OLVASAS_H

// Initializes a matrix. Arguments are strings.
// Data is copied to matrix with a buffer string that is tokenized.

// Inicializál egy mátrix struktúrát. Argumentumai stringek.
// Data először egy bufferbe másolva stringként, majd tokenizálással olvasva doubleként.
Matrix read_matrix(const char *name, const char *height, const char *width, const char *data);

Matrix read_matrix_from_file(const char *name ,FILE *fp);

// takes a filestream and returns a filled Image structure containing all image data.
Image read_image (FILE* fp);



#endif //OLVASAS_H
