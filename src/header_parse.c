#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header_parse.h"

enum ERequestType get_request_type(const char *request)
{
    char buf[10];
    strncpy(buf, request, 10);
    struct request_type_t request_table[] = {
        {"GET", GET},
        {"POST", POST},
        {"HEAD", HEAD},
        {"PUT", PUT},
        {"DELETE", DELETE},
        {"CONNECT", CONNECT},
        {"OPTIONS", OPTIONS},
        {"TRACE", TRACE},
        {"PATCH", PATCH},
        {NULL, UNKNOWN}
    };
    struct request_type_t *p = request_table;
    for(;p->key && strstr(buf, p->key) == NULL; ++p);
    return p->type;
}