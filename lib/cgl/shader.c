#include <cgl/shader.h>
#include <cgl/object.h>
#include <cgl/error.h>
#include <cgl/common.h>
#include <GL/glew.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

/** shader object - only thing besides the ID for the object is the source code for the shader */
struct cgl_shader
{
    unsigned int ID;        /**< object base for the shader object */
    cgl_shader_kind_t kind; /*< kind(type) of a shader */
    char *src;              /**< shader source code */
};

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
 * creates a new cgl_shader struct
 * @return  newly allocated shader object
 */
struct cgl_shader *cgl_shader_new()
{
    struct cgl_shader *sh = NULL;

    sh = (struct cgl_shader *)cgl_malloc(sizeof(struct cgl_shader));
    if (!sh)
    {
        return NULL;
    }

    cgl_object_init((struct cgl_object *)sh);

    sh->kind = cgl_shader_kind_none;
    sh->src = NULL;

    return sh;
}

/**
 * loads the shader source from file
 * @param   sh      shader to use
 * @param   kind    kind of a shader which will be loaded
 * @param   fpath   path to the file to load
 * @return  error code
 */
int cgl_shader_load_source(struct cgl_shader *sh, cgl_shader_kind_t kind, const char *fpath)
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

    cgl_object_set_ID((struct cgl_object *)sh, glCreateShader(kind));
    glShaderSource(cgl_object_get_ID((struct cgl_object *)sh), 1, (const char *const *)&sh->src, NULL);

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
    glCompileShader(cgl_object_get_ID((struct cgl_object *)sh));

    err = check_compile_status(cgl_object_get_ID((struct cgl_object *)sh));
    if (err != 0)
    {
        err = cgl_error_shader_compilation;
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
        cgl_free(sh);
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