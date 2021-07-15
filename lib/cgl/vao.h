#ifndef CGL_VAO_H
#define CGL_VAO_H

#include <cgl/object.h>

struct cgl_vao
{
    struct cgl_object obj;
};

/**
 * initializes the vao struct
 * @param   vao  vertex array object to init
 */
void cgl_vao_init(struct cgl_vao *vao);

/**
 * generates the vertex array object
 * @param   vao  vertex array object to generate
 */
void cgl_vao_gen(struct cgl_vao *vao);

/**
 * unbinds any vao currently bound
 */
void cgl_vao_unbind();

/**
 * binds the given vao
 * @param   vbo  vertex array object to bind
 */
void cgl_vao_bind(struct cgl_vao *vao);

/**
 * frees the given vao
 * @param   vao     vertex array object to free
 */
void cgl_vao_delete(struct cgl_vao *vao);

#endif // CGL_VBO_H