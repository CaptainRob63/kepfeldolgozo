//
// Created by R on 11/7/2024.
//
#include <stdlib.h>
#include <string.h>

#include "util.h"

#include <stdio.h>


// basic string copier. Returns mallocated string. Caller must free.
// alap string másoló. Visszatér egy dinamikusan allokált stringgel. Hívónak felelőssége felszabadítani.

char *strcopy(const char *orig) {
    char *copy = (char*) malloc(strlen(orig) * sizeof(char));
    for (int i = 0; orig[i] != '\0'; i++)
        copy[i] = orig[i];
    return copy;
}

void string_array_free(StringArray strArr) {
    for(int i = 0; i < strArr.size; i++)
        free(strArr.data[i]);
    free(strArr.data);
}