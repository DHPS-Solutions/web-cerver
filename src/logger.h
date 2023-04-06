#ifndef LOGGER_H
#define LOGGER_H

#define LOG_INFO(...)\
({\
    fprintf(stdout, "\033[0;33m[LOG]: ");\
    fprintf(stdout, __VA_ARGS__);\
    fprintf(stdout, "\033[0m\n");\
})

#define LOG_ERR(...)\
({\
    fprintf(stderr, "\033[0;31m[ERR]: ");\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\033[0m\n");\
})

#endif