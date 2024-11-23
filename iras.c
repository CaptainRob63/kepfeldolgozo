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
    char ws = '\0';
    fputs("P6",fp);

    fwrite(&ws, 1, 1, fp);

    for (int i = 0; i < img->comments.size; ++i) {
        fputs(img->comments.data[i], fp);
    }

    fwrite(&ws, 1, 1, fp);

    char width[16], height[16], maxVal[16];
    itoa(img->width, width, 16);
    itoa(img->height, height, 16);
    itoa(img->maxValue, maxVal, 16);

    fputs(width, fp);
    fwrite(&ws, 1, 1, fp);

    fputs(height, fp);
    fwrite(&ws, 1, 1, fp);

    fputs(maxVal, fp);
    fwrite(&ws, 1, 1, fp);

}