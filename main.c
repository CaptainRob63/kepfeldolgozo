#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "olvasas.h"
#include "util.h"
#include "iras.h"
#include "debugmalloc.h"



int main(int argc, char *argv[]) {

/*
    //Matrix matrix = read_matrix("naame", "2", "2", "1 2 3 4");
    Matrix matrix = read_matrix(argv[1], argv[2], argv[3], argv[4]);


    printf("\nMatrix neve : %s\n", matrix.name);
    printf("matrix magassaga: %d\n",matrix.array.height);
    printf("matrix szelessege: %d\n", matrix.array.width);

    printf("matrix adat: ");
    for (int i = 0; i  < matrix.array.height; i++)
        for(int j = 0; j < matrix.array.width; j++)
            printf("%lf ", matrix.array.data[i][j]);
    printf("\n");
*/
    FILE *fp = fopen("matrix.txt", "r");



    if (matrix_find_in_file("asd", fp) == 1) {
        int asd = fgetc(fp);
        printf("%c", asd);
    }


    //matrix_free(&matrix);
    fclose(fp);

/*
    Image img;
    FILE* fp;
    fp = fopen("..\\imgs\\stop01.ppm","rb");
    if (fp == NULL) {
        perror("Error");
        printf("Error: %d (%s)\n", errno);
        strerror(errno);
        return 1;
    }



    img = read_image(fp);

    printf("\n\nheight : %d\nwidht : %d\nmaxval : %d\ntype : %d\n", img.height, img.width, img.maxValue, img.TYPE);

    string_array_print(&img.comments, "commentek");

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            printf("%d %d %d    ", img.array1[i][j].red, img.array1[i][j].green, img.array1[i][j].red);
        }
        printf("\n");
    }

    image_free(&img);
    fclose(fp);
*/


return 0;

}
