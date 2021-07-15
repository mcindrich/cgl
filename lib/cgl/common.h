#ifndef CGL_COMMON_H
#define CGL_COMMON_H

#include <stdlib.h>
#include <GL/glew.h>

#define cgl_malloc(size) (malloc(size))
#define cgl_free(ptr)                                                                                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        free(ptr);                                                                                                     \
        (ptr) = NULL;                                                                                                  \
    } while (0)

enum cgl_buffer_kind_e
{
    cgl_buffer_kind_none = 0,
    cgl_buffer_kind_array = GL_ARRAY_BUFFER,
    cgl_buffer_kind_element = GL_ELEMENT_ARRAY_BUFFER,
};
typedef enum cgl_buffer_kind_e cgl_buffer_kind_t;

enum cgl_draw_kind_e
{
    cgl_draw_kind_none = 0,
    cgl_draw_kind_static = GL_STATIC_DRAW,
    cgl_draw_kind_stream = GL_STREAM_DRAW,
    cgl_draw_kind_dynamic = GL_DYNAMIC_DRAW,
};
typedef enum cgl_draw_kind_e cgl_draw_kind_t;

/**
 * wrapper for glBufferData
 */
#define cgl_buffer_data(buffer, size, data, draw) glBufferData(buffer, size, data, draw)

/**
 * wrapper for glVertexAttribPointer
 */
#define cgl_vertex_attrib_configure(idx, size, type, norm, stride, off)                                                \
    glVertexAttribPointer(idx, size, type, norm, stride, off)

/**
 * wrapper for glEnableVertexAttribArray
 */
#define cgl_vertex_attrib_enable(idx) glEnableVertexAttribArray(idx)

#endif // CGL_COMMON_H