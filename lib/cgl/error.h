#ifndef CGL_ERROR_H
#define CGL_ERROR_H

enum cgl_error_e
{
    cgl_error_none = 0,
    cgl_error_shader_file,
    cgl_error_shader_compilation,
    cgl_error_shader_program_linking,
    cgl_error_COUNT,
};

typedef enum cgl_error_e cgl_error_t;

/**
 * get a description of an error
 * @param   err     error to use
 * @return  error description
 */
const char *cgl_error2str(cgl_error_t err);

#endif // CGL_ERROR_H