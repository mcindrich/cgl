#ifndef CGL_COMMON_H
#define CGL_COMMON_H

#include <stdlib.h>

#define cgl_malloc(size) (malloc(size))
#define cgl_free(ptr)                                                                                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        free(ptr);                                                                                                     \
        (ptr) = NULL;                                                                                                  \
    } while (0)

#endif // CGL_COMMON_H