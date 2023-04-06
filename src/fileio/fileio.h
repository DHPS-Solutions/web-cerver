#ifndef FILEIO_H
#define FILEIO_H
#include <stdlib.h>
#include <stdio.h>

/* Structs */

/**
 * Struct used to represent a file.
 * @param data The file data.
 * @param data_len The data length.
 */
struct file_data_t {
    char *data;
    size_t data_len;
};

/* Methods */

/**
 * Function used to read a file.
 * @param input The file to read.
 * @return The file data.
 */
struct file_data_t *read_file(FILE *input);

#endif