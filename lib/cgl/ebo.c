#include "cgl/object.h"
#include <cgl/ebo.h>
#include <cgl/common.h>

/**
 * initializes the ebo struct
 * @param   ebo  element buffer object to init
 */
void cgl_ebo_init(struct cgl_ebo *ebo)
{
    cgl_object_init((struct cgl_object *)ebo);
}

/**
 * generates the element buffer object
 * @param   ebo  element buffer object to generate
 */
void cgl_ebo_gen(struct cgl_ebo *ebo)
{
    unsigned int tmp;
    glGenBuffers(1, &tmp);
    cgl_object_set_ID((struct cgl_object *)ebo, tmp);
}

/**
 * binds the given ebo to the GL_ELEMENT_ARRAY_BUFFER
 * @param   ebo  element buffer object to bind
 */
void cgl_ebo_bind(struct cgl_ebo *ebo)
{
    glBindBuffer(cgl_buffer_kind_element, cgl_object_get_ID((struct cgl_object *)ebo));
}

/**
 * frees the given ebo
 * @param   ebo     element buffer object to free
 */
void cgl_ebo_delete(struct cgl_ebo *ebo)
{
}