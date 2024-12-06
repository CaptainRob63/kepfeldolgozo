//
// Created by R on 11/2/2024.
//

#include "iras.h"
#include "debugmalloc.h"

#include <stdio.h>
#include <stdlib.h>



void write_matrix(const Matrix *matrix, FILE *fp) {

    char width[3], height[3];
    sprintf(width, "%u", matrix->array.width);
    sprintf(height, "%u", matrix->array.height);

    fprintf(fp,"#%s\n%s %s\n", matrix->name, width, height);

    for (int i = 0; i < matrix->array.height; ++i) {
        for (int j = 0; j < matrix->array.width; ++j)
            fprintf(fp, "%g ", matrix->array.data[i][j]);
        fprintf(fp,"\n");
    }
    fprintf(fp, "\n\n");
}

void write_image_P6(const Image *img, FILE *fp) {
    fputs("P6",fp);

    fwrite("\n", 1, 1, fp);

    for (int i = 0; i < img->comments.size; ++i) {
        fputs(img->comments.data[i], fp);
    }

    fwrite("\n", 1, 1, fp);

    fprintf(fp, "%d %d\n%d\n", img->width, img->height, img->maxValue);

    // print 1byte bitmap
    if (img->array1 != NULL) {
        for (int i = 0; i < img->height; ++i) {
            for (int j = 0; j < img->width; ++j) {
                fwrite(&img->array1[i][j].red,   1, 1, fp);
                fwrite(&img->array1[i][j].green, 1, 1, fp);
                fwrite(&img->array1[i][j].blue,  1, 1, fp);
            }
        }
    }

    // print 2byte bitmap
    if (img->array2 != NULL) {
        for (int i = 0; i < img->height; ++i) {
            for (int j = 0; j < img->width; ++j) {
                fwrite(&img->array2[i][j].red,   2, 1, fp);
                fwrite(&img->array2[i][j].green, 2, 1, fp);
                fwrite(&img->array2[i][j].blue,  2, 1, fp);
            }
        }
    }


}