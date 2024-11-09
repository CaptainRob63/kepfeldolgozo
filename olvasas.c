//
// Created by R on 11/2/2024.
//

#include "olvasas.h"

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



// Initializes a matrix. Arguments are just argv[].
// Data is copied to matrix with a buffer string that is tokenized.

// Inicializál egy mátrix struktúrát. Argumentumai stringek, így argv[] elemei egyszerűen átadhatók neki.
// Data először egy bufferbe másolva stringként, majd tokenizálással olvasva doubleként.

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


Pixel1Byte read_pixel1Byte(char r, char g, char b) {
    Pixel1Byte pixel;

    pixel.red = r;
    pixel.green = g;
    pixel.blue = b;

    return pixel;
}

Pixel2Byte read_pixel2Byte(unsigned short r, unsigned short g, unsigned short b) {
    Pixel2Byte pixel;

    pixel.red = r;
    pixel.green = g;
    pixel.blue = b;

    return pixel;
}

void file_step_till_whitespace(FILE* fp) {
    char byte;
    while(byte != '\n') {
        fread(&byte, 1, 1, fp);
        SHOW("stepped towards new line from hashmark.\n");
    }
}





Img1Byte read_image_1byte(FILE* fp) {
    Img1Byte img;

    //comments start
    img.comments.size = 0;
    int whitespaceCount = 0;
    char currentByte = 0;
    while(whitespaceCount != 4) {
        fread(&currentByte, 1, 1, fp);
        if (currentByte == '#') {
            file_step_till_whitespace(fp);
            img.comments.size++;
        }
        if(isspace(currentByte)) {
            whitespaceCount++;
            SHOW("found whitespace.\n");
        }
    }
    SHOW("comments array size : %d\n", img.comments.size);
    SHOW("header whitespace and comment counted.\n");

    long int headerSize = ftell(fp) + 1;
    fseek(fp, 0, SEEK_SET);

    char *header = (char*) malloc(headerSize * sizeof(char));
    for (int i = 0; i < headerSize; ++i) {
        fread(&header[i], 1, 1, fp);
    }
    header[headerSize] = '\0';

    char *headerCopy = strcopy(header);

    SHOW("header read and copied.\nheader : %s\ncopy : %s\n", header, headerCopy);

    StringArray tempComments;
    tempComments.data = (char**) malloc(img.comments.size * sizeof(char*));
    tempComments.size = img.comments.size;
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

    string_array_print(&tempComments);

    img.comments.data = (char**) malloc(img.comments.size * sizeof(char*));
    if(img.comments.data == NULL)
        fprintf(stderr,"comment string array could not be malloced.\n");


    for (i = 0; i < img.comments.size; i++)
        img.comments.data[i] = strcopy(tempComments.data[i]);



    free(headerCopy);
    SHOW("headercopy freed.\n");
    free(tempComments.data);
    SHOW("comments done.\n");

    //comments done

    sscanf((header), "P%d", &img.TYPE); //type

    SHOW("type scanned.\n");

    char headerWithoutComment[100];
    i = 0;
    j = 0;
    while(header[i] != '\0') {
        if(header[i] == '#') {
            while (header[i] != '\n')
                i++;
        }
        headerWithoutComment[j++] = header[i++];
    }
    headerWithoutComment[j] = '\0';
    SHOW("header without comment copied.");

    char *token;


    token = strtok(headerWithoutComment, " \t\n\v\f\r" );
    sscanf(token, "P%d", &img.TYPE);

    token = strtok(NULL, " \t\n\v\f\r");
    img.width = atoi(token);

    token = strtok(NULL, " \t\n\v\f\r");
    img.height = atoi(token);

    token = strtok(NULL, " \t\n\v\f\r");
    img.maxValue = atoi(token);

    SHOW("header done");
    //header done


    free(header);
    fclose(fp);
    return img;
}

