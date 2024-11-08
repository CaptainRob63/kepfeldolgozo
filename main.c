#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "olvasas.h"
#include "util.h"
#include "iras.h"



int main(int argc, char *argv[]) {

/*
    Matrix matrix = read_matrix(argv[1], argv[2], argv[3], argv[4]);

    for (int i = 0; i  < matrix.array.height; i++)
        for(int j = 0; j < matrix.array.width; j++)
            printf("%lf ", matrix.array.data[i][j]);
    printf("\n");

    printf("%s\n", matrix.name);


    free(matrix.array.data);
*/



    Img1Byte img;
    FILE* fp;
    fp = fopen("\\Users\\R\\Downloads","rb");
    if(fp == NULL)
        return 1;
    img = read_image_1byte(fp);


    fclose(fp);



    char cwd[100];
    _wgetcwd(cwd, 100);
    printf("%s", cwd);
    return 0;
}
