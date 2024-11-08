//
// Created by R on 11/2/2024.
//
#pragma once

#include <stdio.h>
#include "util.h"

#ifndef OLVASAS_H
#define OLVASAS_H


Matrix read_matrix(const char *name, const char *height, const char *width, const char *data);

Pixel1Byte read_pixel_1byte(char r, char g, char b);
Pixel2Byte read_pixel_2byte(unsigned short r, unsigned short g, unsigned short b);

Img1Byte read_image_1byte (FILE* fp);



#endif //OLVASAS_H
