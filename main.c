#include <stdio.h>
#include <stdlib.h>

#include "olvasas.h"
#include "util.h"
#include "iras.h"



int main(int argc, char *argv[]) {


    Matrix matrix = read_matrix(argv[1], argv[2], argv[3], argv[4]);

    for (int i = 0; i  < matrix.array.height; i++)
        for(int j = 0; j < matrix.array.width; j++)
            printf("%lf ", matrix.array.data[i][j]);
    printf("\n");

    printf("%s\n", matrix.name);


    free(matrix.array.data);



    return 0;
}
