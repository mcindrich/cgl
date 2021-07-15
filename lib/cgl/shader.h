#ifndef CGL_SHADER_H
#define CGL_SHADER_H

#include <cgl/object.h>
#include <GL/glew.h>
#include <cgl/types.h>

enum cgl_shader_kind_e
{
    cgl_shader_kind_none = 0,
    cgl_shader_kind_vertex = GL_VERTEX_SHADER,
    cgl_shader_kind_fragment = GL_FRAGMENT_SHADER,
    cgl_shader_kind_geometry = GL_GEOMETRY_SHADER,
};
typedef enum cgl_shader_kind_e cgl_shader_kind_t;

enum cgl_shader_flag_e : u8_t
{
    cgl_shader_flag_initialized = 0x1,
    cgl_shader_flag_compiled = 0x2,
};
typedef enum cgl_shader_flag_e cgl_shader_flag_t;

/** shader object */
struct cgl_shader
{
    struct cgl_object obj;   /**< object base for the shader object */
    cgl_shader_kind_t kind;  /*< kind(type) of a shader */
    char *src;               /**< shader source code */
    cgl_shader_flag_t flags; /**< shader flags */
};

/**
 * check if a flag is set or not
 * @param   sh      shader to use
 * @param   flg     flag to check
 * @return  1 if a flag is set, 0 otherwise
 */
#define cgl_shader_check_flag(sh, flg) (((sh)->flags) & (flg))

/**
 * initializes the shader struct
 * @param   sh      shader to init
 */
void cgl_shader_init(struct cgl_shader *sh);

/**
 * loads the shader source from file
 * @param   sh      shader to use
 * @param   kind    kind of a shader which will be loaded
 * @param   fpath   path to the file to load
 * @return  error code
 */
int cgl_shader_load_source(struct cgl_shader *sh, cgl_shader_kind_t kind, const char *fpath);

/**
 * compile the given shader object
 * @param   sh      shader to compile once the source has been loaded
 * @return  error code
 */
int cgl_shader_compile(struct cgl_shader *sh);

/**
 * writes the compile info inside of a given buffer
 * @param   sh      shader to use
 * @param   buffer  buffer to use
 * @param   max     max chars in a buffer
 */
void cgl_shader_compile_info(struct cgl_shader *sh, char *buffer, size_t max);

/**
 * frees the given cgl_shader
 * @param   sh     shader to free
 */
void cgl_shader_delete(struct cgl_shader *sh);

#endif // CGL_SHADER_H