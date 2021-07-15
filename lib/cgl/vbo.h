#ifndef CGL_VBO_H
#define CGL_VBO_H

#include <cgl/object.h>
#include <cgl/types.h>

struct cgl_vbo
{
    struct cgl_object obj;
};

/**
 * initializes the vbo struct
 * @param   vbo  vertex buffer object to init
 */
void cgl_vbo_init(struct cgl_vbo *vbo);

/**
 * generates the vertex buffer object
 * @param   vbo  vertex buffer object to generate
 */
void cgl_vbo_gen(struct cgl_vbo *vbo);

/**
 * binds the given vbo to the GL_ARRAY_BUFFER
 * @param   vbo  vertex buffer object to bind
 */
void cgl_vbo_bind(struct cgl_vbo *vbo);

/**
 * frees the given vbo
 * @param   vao     vertex buffer object to free
 */
void cgl_vbo_delete(struct cgl_vbo *vbo);

#endif // CGL_VBO_H