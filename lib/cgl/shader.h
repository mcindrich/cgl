#ifndef CGL_SHADER_H
#define CGL_SHADER_H

#include <cgl/object.h>
#include <cgl/types.h>

enum cgl_shader_kind
{
    cgl_shader_kind_none = 0,
    cgl_shader_kind_vertex = 0x8B31,
    cgl_shader_kind_fragment = 0x8B30,
    cgl_shader_kind_geometry = 0x8DD9,
};

enum cgl_shader_flag : u8_t
{
    cgl_shader_flag_initialized = 0x1,
    cgl_shader_flag_compiled = 0x2,
};

/** shader object */
struct cgl_shader
{
    struct cgl_object obj;      /**< object base for the shader object */
    enum cgl_shader_kind kind;  /*< kind(type) of a shader */
    char *src;                  /**< shader source code */
    enum cgl_shader_flag flags; /**< shader flags */
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
int cgl_shader_load_source(struct cgl_shader *sh, enum cgl_shader_kind kind, const char *fpath);

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
