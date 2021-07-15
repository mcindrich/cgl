#include "cgl/object.h"
#include <cgl/vao.h>
#include <GL/glew.h>

/**
 * initializes the vao struct
 * @param   vao  vertex array object to init
 */
void cgl_vao_init(struct cgl_vao *vao)
{
    cgl_object_init((struct cgl_object *)vao);
}

/**
 * generates the vertex array object
 * @param   vao  vertex array object to generate
 */
void cgl_vao_gen(struct cgl_vao *vao)
{
    unsigned int tmp;
    glGenVertexArrays(1, &tmp);
    cgl_object_set_ID((struct cgl_object *)vao, tmp);
}

/**
 * binds the given vao
 * @param   vbo  vertex array object to bind
 */
void cgl_vao_bind(struct cgl_vao *vao)
{
    glBindVertexArray(cgl_object_get_ID((struct cgl_object *)vao));
}

/**
 * unbinds any vao currently bound
 */
void cgl_vao_unbind()
{
    glBindVertexArray(0);
}

/**
 * frees the given vao
 * @param   vao     vertex array object to free
 */
void cgl_vao_delete(struct cgl_vao *vao)
{
}