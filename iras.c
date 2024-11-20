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
