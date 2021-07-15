#include <cgl/error.h>

/**
 * get a description of an error
 * @param   err     error to use
 * @return  error description
 */
const char *cgl_error2str(cgl_error_t err)
{
    const char *map[] = {
        [cgl_error_none] = "no error",
        [cgl_error_shader_file] = "unable to read given shader file",
        [cgl_error_shader_compilation] = "unable to compile shader",
        [cgl_error_shader_program_linking] = "unable to link the program",
    };
    const char *unkn = "unknown error";
    const char *err_str = unkn;

    if (err >= cgl_error_none && err < cgl_error_COUNT)
    {
        err_str = map[err];
    }

    return err_str;
}