#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "olvasas.h"
#include "util.h"
#include "iras.h"



int main(int argc, char *argv[]) {


    Matrix matrix = read_matrix(argv[1], argv[2], argv[3], argv[4]);

    printf("\nMatrix neve : %s\n", matrix.name);
    printf("matrix magassaga: %d\n",matrix.array.height);
    printf("matrix szelessege: %d\n", matrix.array.width);

    printf("matrix adat: ");
    for (int i = 0; i  < matrix.array.height; i++)
        for(int j = 0; j < matrix.array.width; j++)
            printf("%lf ", matrix.array.data[i][j]);
    printf("\n");



    free(matrix.array.data);

    Img1Byte img;
    FILE* fp;
    fp = fopen(argv[5],"rb");
    if (fp == NULL) {
        perror("Error");
        printf("Error: %d (%s)\n", errno);
        strerror(errno);
        return 1;
    }

    img = read_image_1byte(fp);

    printf("\n\nheight : %d\nwidht : %d\nmaxval : %d\ntype : %d\n", img.height, img.width, img.maxValue, img.TYPE);

    string_array_print(&img.comments, "commentek");

    fclose(fp);

return 0;

}
