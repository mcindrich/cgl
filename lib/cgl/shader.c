#include <cgl/shader.h>
#include <cgl/object.h>
#include <cgl/error.h>
#include <cgl/common.h>
#include <GL/glew.h>
#include <stdio.h>

/**
 * set a specific flag for a shader
 * @param   sh      shader to use
 * @param   flg     flag to set
 */
#define cgl_shader_set_flag(sh, flg) ((sh)->flags |= flg)

/**
 * reads and loads the file in memory
 * @param   fpath   path to the file to load
 * @return  read data or NULL on error
 */
static char *load_shader_source(const char *fpath);

/**
 * checks if any compile errors have occured when compiling the shader
 * @param   ID      opengl shader ID
 * @return  0 = OK, 1 = errors
 */
static int check_compile_status(unsigned int ID);

/**
 * initializes the shader struct
 * @param   sh      shader to init
 */
void cgl_shader_init(struct cgl_shader *sh)
{
    cgl_object_init((struct cgl_object *)sh);
    sh->src = NULL;
    sh->kind = cgl_shader_kind_none;
    sh->flags = 0;
}

/**
 * loads the shader source from file
 * @param   sh      shader to use
 * @param   kind    kind of a shader which will be loaded
 * @param   fpath   path to the file to load
 * @return  error code
 */
int cgl_shader_load_source(struct cgl_shader *sh, enum cgl_shader_kind kind, const char *fpath)
{
    int err = cgl_error_none;
    char *data = NULL;

    data = load_shader_source(fpath);
    if (!data)
    {
        return cgl_error_shader_file;
    }

    sh->src = data;
    sh->kind = kind;

    return err;
}

/**
 * compile the given shader object
 * @param   sh      shader to compile once the source has been loaded
 * @return  error code
 */
int cgl_shader_compile(struct cgl_shader *sh)
{
    int err = cgl_error_none;

    cgl_object_set_ID((struct cgl_object *)sh, glCreateShader(sh->kind));
    glShaderSource(cgl_object_get_ID((struct cgl_object *)sh), 1, (const char *const *)&sh->src, NULL);

    cgl_shader_set_flag(sh, cgl_shader_flag_initialized);

    glCompileShader(cgl_object_get_ID((struct cgl_object *)sh));

    err = check_compile_status(cgl_object_get_ID((struct cgl_object *)sh));
    if (err != 0)
    {
        err = cgl_error_shader_compilation;
    }
    else
    {
        cgl_shader_set_flag(sh, cgl_shader_flag_compiled);
    }
    return err;
}

/**
 * writes the compile info inside of a given buffer
 * @param   sh      shader to use
 * @param   buffer  buffer to use
 * @param   max     max chars in a buffer
 */
void cgl_shader_compile_info(struct cgl_shader *sh, char *buffer, size_t max)
{
    glGetShaderInfoLog(cgl_object_get_ID((struct cgl_object *)sh), max, NULL, buffer);
}

/**
 * frees the given cgl_shader
 * @param   sh     shader to free
 */
void cgl_shader_delete(struct cgl_shader *sh)
{
    if (sh)
    {
        glDeleteShader(cgl_object_get_ID((struct cgl_object *)sh));
        if (sh->src)
        {
            cgl_free(sh->src);
        }
    }
}

/**
 * reads and loads the file in memory
 * @param   fpath   path to the file to load
 * @return  read data or NULL on error
 */
static char *load_shader_source(const char *fpath)
{
    char *buffer = 0;
    unsigned long length = 0;
#define _CRT_SECURE_NO_WARNINGS
    FILE *f = fopen(fpath, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = (char *)malloc(sizeof(char) * (length + 1));
        if (buffer)
        {
            fread(buffer, sizeof(char), length, f);
            buffer[length] = 0;
        }
        fclose(f);
    }
    return buffer;
}

/**
 * checks if any compile errors have occured when compiling the shader
 * @param   ID      opengl shader ID
 * @return  0 = OK, 1 = errors
 */
static int check_compile_status(unsigned int ID)
{
    int success;

    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        return 1;
    }
    return 0;
}
