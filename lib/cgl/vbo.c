#include <cgl/object.h>
#include <cgl/vbo.h>
#include <cgl/common.h>
#include <GL/glew.h>

/**
 * initializes the vbo struct
 * @param   vbo  vertex buffer object to init
 */
void cgl_vbo_init(struct cgl_vbo *vbo)
{
    cgl_object_init((struct cgl_object *)vbo);
}

/**
 * generates the vertex buffer object
 * @param   vbo  vertex buffer object to generate
 */
void cgl_vbo_gen(struct cgl_vbo *vbo)
{
    unsigned int tmp;
    glGenBuffers(1, &tmp);
    cgl_object_set_ID((struct cgl_object *)vbo, tmp);
}

/**
 * binds the given vbo to the GL_ARRAY_BUFFER
 * @param   vbo  vertex buffer object to bind
 */
void cgl_vbo_bind(struct cgl_vbo *vbo)
{
    glBindBuffer(cgl_buffer_kind_array, cgl_object_get_ID((struct cgl_object *)vbo));
}

/**
 * frees the given vbo
 * @param   vbo     vertex buffer object to free
 */
void cgl_vbo_delete(struct cgl_vbo *vbo)
{
}