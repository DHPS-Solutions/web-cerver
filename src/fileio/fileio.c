#include <stdlib.h>
#include <stdio.h>

#include "fileio.h"

struct file_data_t *read_file(FILE *input)
{
    if (input == NULL)
        return NULL;
    
    struct file_data_t *res = (struct file_data_t *)
                                (malloc(sizeof(struct file_data_t)));

    fseek(input, 0, SEEK_END);

    res->data_len = ftell(input);

    rewind(input);

    res->data = (char *)(malloc(res->data_len * sizeof(char)));

    if (fread(res->data, sizeof(char), res->data_len, input) != res->data_len)
        return NULL;

    return res;
}

void free_file_data(struct file_data_t *file_data)
{
    if (file_data == NULL)
        return;
    
    free(file_data->data);
    free(file_data);
}