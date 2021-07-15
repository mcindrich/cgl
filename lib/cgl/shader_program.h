#ifndef CGL_SHADER_PROGRAM_H
#define CGL_SHADER_PROGRAM_H

#include <cgl/shader.h>

/** shader_program object - has vertex/fragment/geometry shaders */
struct cgl_shader_program
{
    struct cgl_object obj;       /**< object base for the shader_program object */
    struct cgl_shader *v_shader; /**< vertex shader */
    struct cgl_shader *f_shader; /**< fragment shader */
    struct cgl_shader *g_shader; /**< geometry shader */
};

/**
 * initializes the shader_program struct
 * @param   prog  program to init
 */
void cgl_shader_program_init(struct cgl_shader_program *prog);

/**
 * sets the vertex shader for a program
 * @param   prog    program to use
 * @param   sh      shader to set
 */
void cgl_shader_program_set_vertex_shader(struct cgl_shader_program *prog, struct cgl_shader *sh);

/**
 * sets the fragment shader for a program
 * @param   prog    program to use
 * @param   sh      shader to set
 */
void cgl_shader_program_set_fragment_shader(struct cgl_shader_program *prog, struct cgl_shader *sh);

/**
 * sets the geometry shader for a program
 * @param   prog    program to use
 * @param   sh      shader to set
 */
void cgl_shader_program_set_geometry_shader(struct cgl_shader_program *prog, struct cgl_shader *sh);

/**
 * sets the program to be the currently running program
 * @param   prog    program to use
 */
void cgl_shader_program_use(struct cgl_shader_program *prog);

/**
 * links the shaders used by a program
 * @param   prog    program to use
 * @return  error code
 */
int cgl_shader_program_link(struct cgl_shader_program *prog);

/**
 * writes the link info inside of a given buffer
 * @param   prog    shader program to use
 * @param   buffer  buffer to use
 * @param   max     max chars in a buffer
 */
void cgl_shader_program_link_info(struct cgl_shader_program *prog, char *buffer, size_t max);

/**
 * frees the given cgl_shader_program
 * @param   prog     shader_program to free
 */
void cgl_shader_program_delete(struct cgl_shader_program *prog);

#endif // CGL_SHADER_PROGRAM_H