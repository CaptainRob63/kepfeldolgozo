//
// Created by R on 11/7/2024.
//
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "debugmalloc.h"

#include <stdio.h>
#include <wchar.h>


char *strcopy(const char *orig) {
    int orig_length  = strlen(orig);

    char *copy = (char*) malloc((orig_length + 1) * sizeof(char));
    if (copy == NULL)
        return NULL;

    for (int i = 0; orig[i] != '\0'; i++)
        copy[i] = orig[i];
    copy[orig_length] = '\0';

    return copy;
}

void str_newline_to_zero(char *str) {
    for (int i = 0; str[i] != '\0' ; ++i)
        if (str[i] == '\n')
            str[i] = '\0';
}



void string_array_print(StringArray *strArr, char *name) {
    for (int i = 0; i < strArr->size; i++) {
        printf("%s[%d] : %s\n", name ,i, strArr->data[i]);
    }
}

void string_array_free(StringArray *strArr) {
    if (strArr->size == 0)
        return;

    for(int i = 0; i < strArr->size; i++) {
        free(strArr->data[i]);
        printf("string freed\n");
    }
    free(strArr->data);
}


void image_free(Image *img) {
    for (int i = 0; i < img->comments.size; ++i)
        free(img->comments.data[i]);
    free(img->comments.data);

    if (img->array1 != NULL) {
        for (int i = 0; i < img->height; i++)
            free(img->array1[i]);
        free(img->array1);
    }

    if (img->array2 != NULL) {
        for (int i = 0; i < img->height; i++)
            free(img->array2[i]);
        free(img->array2);
    }
}

void matrix_free(Matrix *matrix) {
    free(matrix->array.data[0]);
    free(matrix->array.data);
}


int8_t matrix_find_in_file(const char *name, FILE *fp) {
    char c = '\0';
    char currentName[32];

    while(c != EOF) {
        c = fgetc(fp);
        if (c == '#') {
            fgets(currentName, 32, fp);

            str_newline_to_zero(currentName);

            if (currentName == NULL)
                return -1;

            if(strcmp(currentName, name) == 0)
                return 1;

        }
    }

    return 0;
}

