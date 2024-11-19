//
// Created by R on 11/2/2024.
//

#include "iras.h"
#include "debugmalloc.h"

#include <stdio.h>
#include <stdlib.h>

void write_matrix(const Matrix *matrix, FILE *fp) {

    char width[2], height[2];
    sprintf(width, "%d", matrix->array.width);
    sprintf(height, "%d", matrix->array.height);

    fprintf(fp,"#%s\n%s %s\n", matrix->name, width, height);

    char number[100+1];
    for (int i = 0; i < matrix->array.height; ++i) {
        for (int j = 0; j < matrix->array.width; ++j)
            fprintf(fp, "%g ", matrix->array.data[i][j]);
        fprintf(fp,"\n");
    }
    fprintf(fp, "\n\n");
}
