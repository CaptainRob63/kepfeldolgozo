//
// Created by R on 11/2/2024.
//

#include "olvasas.h"
#include "debugmalloc.h"

#include <ctype.h>
#include <stdbool.h>

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG

#ifdef DEBUG
#define SHOW printf
#else
#define SHOW // macros
#endif





Matrix read_matrix(const char *name, const char *height, const char *width,  const char *data) {
    Matrix matrix;

    for (int i = 0; i < 32; i++)
        matrix.name[i] = '\0';

    for (int i = 0; name[i] != '\0'; i++) {
        matrix.name[i] = name[i];
        SHOW("copied 1 char to matrix name\n");
    }


    matrix.array.height = atof(height);
    matrix.array.width = atof(width);
    SHOW("set matrix height and width\n");


    matrix.array.data = (double**) malloc(matrix.array.height * sizeof(double));
    matrix.array.data[0] = (double*) malloc(matrix.array.width * matrix.array.height * sizeof(double));

    for (int i = 0; i < matrix.array.height; i++)
        matrix.array.data[i] = matrix.array.data[0] + i * matrix.array.width;


    char *databuffer = strcopy(data);
    char *tok = strtok(databuffer, " ");
    SHOW("token : %s\n", tok);

    for (int i = 0; i < matrix.array.height; i++) {
        for (int j = 0; j <matrix.array.width; j++) {
            matrix.array.data[i][j] = atof(tok);
            tok = strtok(NULL, " ");
        }
    }
    free(databuffer);

    return matrix;
}

Matrix read_matrix_from_file(const char *name, FILE *fp) {
    char *width[2],
         *heigth[2];
    fgets(width, 2, fp);
    fgets(heigth, 2, fp);

    char *array = (char*) malloc(atoi(width) * atoi(heigth) * sizeof(char));

    fgets()

    free(array);
    return matrix;
}




void file_step_till_whitespace(FILE* fp) {
    char byte;
    while(byte != '\n') {
        fread(&byte, 1, 1, fp);
        SHOW("stepped towards new line from hashmark.\n");
    }
}





// first counts header size, simultainously counting the number of comments.
// then mallocs a header string, fills it and returns it.
// leaves file pointer just before the bitmap.
static char *read_header_to_string(Image *img, FILE* fp) {

    img->comments.size = 0;
    int whitespaceCount = 0;
    char currentByte = 0;
    while(whitespaceCount != 4) {
        fread(&currentByte, 1, 1, fp);
        if (currentByte == '#') {
            file_step_till_whitespace(fp);
            img->comments.size++;
        }
        if(isspace(currentByte)) {
            whitespaceCount++;
            SHOW("found whitespace.\n");
        }
    }
    SHOW("comments array size : %d\n", img->comments.size);
    SHOW("header whitespace and comment counted.\n");


    long int headerSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);


    char *header = (char*) malloc((headerSize+1) * sizeof(char));
    for (int i = 0; i < headerSize; ++i) {
        fread(&header[i], 1, 1, fp);
    }
    header[headerSize] = '\0';

    return header;
}




// copies header string which is then mangled: it creates "parasitic" strings inside that copy, by changing the next newline after a hashmark to a terminating zero.
// it then fills an array of strings with these "substrings", before actually copying them to the image structure.
static void read_comments_array_to_img(Image *img, char *header) {
    char *headerCopy = strcopy(header);

    StringArray tempComments;
    tempComments.data = (char**) malloc(img->comments.size * sizeof(char*));
    tempComments.size = img->comments.size;
    SHOW("tempComments malloced. %p\n", tempComments.data);

    int i = 0;
    int j = 0;
    while (headerCopy[i] != '\0') {
        if(headerCopy[i] == '#') {
            tempComments.data[j++] = &headerCopy[i];
            while (headerCopy[i] != '\n')
                i++;
            headerCopy[i] = '\0';
        }
        i++;
    }
    SHOW("tempComments filled.\n");


    img->comments.data = (char**) malloc(img->comments.size * sizeof(char*));
    if(img->comments.data == NULL)
        fprintf(stderr,"comment string array could not be malloced.\n");


    for (i = 0; i < img->comments.size; i++)
        img->comments.data[i] = strcopy(tempComments.data[i]);

    free(headerCopy);
    free(tempComments.data);

}




// goes through a header string character by character, skipping over comments, and copying the rest.
static void generate_header_without_comment(char *headerWithoutComment, const char *header) {

    int i = 0;
    int j = 0;
    while(header[i] != '\0') {
        if(header[i] == '#') {
            while (header[i] != '\n')
                i++;
        }
        headerWithoutComment[j++] = header[i++];
    }
    headerWithoutComment[j] = '\0';
}




// header without comment can be trivially tokenized with newline characters as a delimiter.
static void read_header_wo_comment_to_img(Image *img, char *headerWithoutComment) {
    char *token;

    token = strtok(headerWithoutComment, " \t\n\v\f\r" );
    sscanf(token, "P%d", &img->TYPE);

    token = strtok(NULL, " \t\n\v\f\r");
    img->width = atoi(token);

    token = strtok(NULL, " \t\n\v\f\r");
    img->height = atoi(token);

    token = strtok(NULL, " \t\n\v\f\r");
    img->maxValue = atoi(token);

}


static void read_bitmap_1byte(Image *img, FILE* fp) {
    img->array1 = (Pixel1Byte**) malloc(img->height * sizeof(Pixel1Byte*));
    for (int i = 0; i < img->height; ++i) 
        img->array1[i] = (Pixel1Byte*) malloc(img->width * sizeof(Pixel1Byte));

    img->array2 = NULL;
    
    for (int i = 0; i < img->height; ++i) {
        for (int j = 0; j < img->width; ++j) {
            fread(&img->array1[i][j].red, 1, 1, fp);
            fread(&img->array1[i][j].green, 1, 1, fp);
            fread(&img->array1[i][j].blue, 1, 1, fp);
        }
    }
}

static void read_bitmap_2byte(Image *img, FILE* fp) {
    img->array2 = (Pixel2Byte**) malloc(img->height * sizeof(Pixel2Byte*));
    for (int i = 0; i < img->height; ++i) 
        img->array2[i] = (Pixel2Byte*) malloc(img->width * sizeof(Pixel2Byte));

    img->array1 = NULL;

    for (int i = 0; i < img->height; ++i) {
        for (int j = 0; j < img->width; ++j) {
            fread(&img->array2[i][j].red, 2, 1, fp);
            fread(&img->array2[i][j].green, 2, 1, fp);
            fread(&img->array2[i][j].blue, 2, 1, fp);
        }
    }
}




// so simple! definitely did not take 5 hours to write !!! (◡‿◡✿)
Image read_image(FILE* fp) {
    Image img;

    char *header = read_header_to_string(&img, fp);

    read_comments_array_to_img(&img, header);

    char headerWithoutComment[100];
    generate_header_without_comment(headerWithoutComment, header);

    read_header_wo_comment_to_img(&img, headerWithoutComment);

    free(header);

    if (img.maxValue < 256)
        read_bitmap_1byte(&img, fp);
    else if (img.maxValue < 65536)
        read_bitmap_2byte(&img, fp);
    else
        fprintf(stderr,"Incorrect maximum pixel brightness value read.");

    return img;
}



