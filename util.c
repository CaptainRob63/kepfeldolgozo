//
// Created by R on 11/7/2024.
//
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "debugmalloc.h"

#include <stdio.h>
#include <wchar.h>


// basic string copier. Returns mallocated string. Caller must free.
// alap string másoló. Visszatér egy dinamikusan allokált stringgel. Hívónak felelőssége felszabadítani.

char *strcopy(const char *orig) {
    char *copy = (char*) malloc(strlen(orig) * sizeof(char));
    for (int i = 0; orig[i] != '\0'; i++)
        copy[i] = orig[i];
    return copy;
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