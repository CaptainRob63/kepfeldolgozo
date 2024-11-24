#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "olvasas.h"
#include "util.h"
#include "iras.h"
#include "debugmalloc.h"



double matrix_normalisation_constant(Matrix matrix) {
    double acc = 0;
    for (int i = 0; i < matrix.array.height; ++i) {
        for (int j = 0; j < matrix.array.width; ++j) {
            acc += matrix.array.data[i][j];
        }
    }

    // holy ward spell against magic numbers
    float EPSILON = 0.1;
    if (abs(acc) < EPSILON) // if (acc == 0)
        return 1;

    return acc;
}


void process_pixel(Image *img, int x, int y, Matrix matrix, double norm) {
    double accR = 0;
    double accG = 0;
    double accB = 0;

    int startPosX = x - (matrix.array.width  - 1) / 2;
    int startPosY = y - (matrix.array.height - 1) / 2;

    for (int i = 0; i < matrix.array.height; ++i) {
        for (int j = 0; j < matrix.array.width; ++j) {

            if (startPosX + j  <  0            |
                startPosX + j  >=  img->width  |
                startPosY + i  <  0            |
                startPosY + i  >=  img->height )

                {
                norm -= matrix.array.data[i][j];
                continue;
            }


            accR += matrix.array.data[i][j] * img->array1 [startPosY + i]  [startPosX + j].red;
            accG += matrix.array.data[i][j] * img->array1 [startPosY + i]  [startPosX + j].green;
            accB += matrix.array.data[i][j] * img->array1 [startPosY + i]  [startPosX + j].blue;

            //printf("%d %d\n", startPosX+j, startPosY+i);
        }
    }


    //printf("%g %g %g\n",accR, accG, accB);
    //1275
    //-1020

   /* accR += 500;
    accR /= 1275 + 1020;
    accR *= 256;

    accB += 500;
    accB /= 1275 + 1020;
    accB *= 256;

    accG += 500;
    accG /= 1275 + 1020;
    accG *= 256;*/

    img->array1[y][x].red   =  accR / norm;
    img->array1[y][x].green =  accG / norm;
    img->array1[y][x].blue  =  accB / norm;
    //printf("%d %d\n",x,y);
}

void process_image(Image *img, Matrix matrix) {
    double norm = matrix_normalisation_constant(matrix);

    for (int i = 0; i < img->height; ++i)
        for (int j = 0; j < img->width; ++j)
            process_pixel(img, j, i, matrix, norm);

}


int main(int argc, char *argv[]) {

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
    fclose(fp);

    Matrix matrix = read_matrix("asdasdasd", "3", "3", "0 -1 0 -1 4 -1 0 -1 0");

    fp = fopen("img.ppm", "wb");


    process_image(&img, matrix);

    write_image_P6(&img, fp);

    matrix_free(&matrix);
    image_free(&img);
/*
    Matrix matrix = read_matrix("asdasdasd", "4", "3", "1 2 3 4 5 6 7 8 9 10 11 12");
    //Matrix matrix = read_matrix(argv[1], argv[2], argv[3], argv[4]);
    MATRIX_ERROR mtxError = matrix_check_error(matrix);
    matrix_write_error(mtxError);
    if (mtxError != MATERR_NONE) {
        return 1;
    }




    FILE *fp = fopen("matrix.txt", "a");

    //Matrix matrix = read_matrix_from_file("asd", fp);

    //printf("%s\n", matrix.name);
    //printf("%u %u", matrix.array.width, matrix.array.height);

    write_matrix(&matrix, fp);
    matrix_free(&matrix);
    fclose(fp);
*/
/*


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
