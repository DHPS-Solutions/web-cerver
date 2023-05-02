#ifndef HEADER_PARSE_H
#define HEADER_PARSE_H

#include <stdlib.h>
#include <string.h>

#define REQUEST_TYPE_COUNT 10

/**
 * Enum for request types 
 */
enum ERequestType {
    GET,
    POST,
    HEAD,
    PUT,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH,
    UNKNOWN
};

/**
 * Struct for request type
 */
struct request_type_t {
    char *key;
    enum ERequestType type;
};

/**
 * Function for getting request type
 * @param request - request string
 * @return request type
 */
enum ERequestType get_request_type(const char *request);

#endif