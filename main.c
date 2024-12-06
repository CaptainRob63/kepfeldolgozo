#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "olvasas.h"
#include "util.h"
#include "iras.h"
#include "process.h"
#include "debugmalloc.h"







int main(int argc, char *argv[]) {

    if (strcmp(argv[1], "addKernel") == 0) {
        FILE *matrices = fopen("matrix.txt", "a");
        Matrix matrix = read_matrix(argv[2], argv[3], argv[4], argv[5]);
        write_matrix(&matrix, matrices);
        matrix_free(&matrix);
    }

    if (strcmp(argv[1], "process") == 0) {
        FILE *original = fopen(argv[2], "rb");
        Image image = read_image(original);
        fclose(original);

        FILE *matrices = fopen("matrix.txt", "r");
        Matrix matrix = read_matrix_from_file(argv[4], matrices);
        fclose(matrices);

        FILE *processed = fopen(argv[3], "wb");
        process_image(&image, matrix);
        write_image_P6(&image, processed);

        fclose(processed);
        image_free(&image);
        matrix_free(&matrix);
    }

return 0;

}
