#include "../include/helper.h"
#include "stdio.h"
#include "stdlib.h"

char *read_file(char *path) {
    FILE *file = fopen(path, "r");

    if(file == NULL) { 
        return '\0';
        perror("Error open file");
    }

    fseek(file, 10, SEEK_END);
    long size_code = ftell(file);
    rewind(file);

    char *code = (char *)malloc(size_code + 1);

    fread(code, 1, size_code, file);

    return code;

    free(code);
}