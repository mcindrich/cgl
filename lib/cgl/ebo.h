#ifndef CGL_EBO_H
#define CGL_EBO_H

#include <cgl/object.h>

struct cgl_ebo
{
    struct cgl_object obj;
};

/**
 * initializes the ebo struct
 * @param   ebo  element buffer object to init
 */
void cgl_ebo_init(struct cgl_ebo *ebo);

/**
 * generates the element buffer object
 * @param   ebo  element buffer object to generate
 */
void cgl_ebo_gen(struct cgl_ebo *ebo);

/**
 * binds the given ebo to the GL_ELEMENT_ARRAY_BUFFER
 * @param   ebo  element buffer object to bind
 */
void cgl_ebo_bind(struct cgl_ebo *ebo);

/**
 * frees the given ebo
 * @param   ebo     element buffer object to free
 */
void cgl_ebo_delete(struct cgl_ebo *ebo);

#endif // CGL_VBO_H