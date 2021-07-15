#include <cgl/shader_program.h>
#include <cgl/object.h>
#include <cgl/common.h>
#include <cgl/error.h>

/**
 * check linking status for a program
 * @param   ID      program ID
 * @return 0 = OK, 1 = errors
 */
static int check_link_status(unsigned int ID);

/**
 * initializes the shader_program struct
 * @param   prog  program to init
 */
void cgl_shader_program_init(struct cgl_shader_program *prog)
{
    cgl_object_init((struct cgl_object *)prog);
    prog->v_shader = NULL;
    prog->f_shader = NULL;
    prog->g_shader = NULL;
}

/**
 * sets the vertex shader for a program
 * @param   prog    program to use
 * @param   sh      shader to set
 */
void cgl_shader_program_set_vertex_shader(struct cgl_shader_program *prog, struct cgl_shader *sh)
{
    prog->v_shader = sh;
}

/**
 * sets the fragment shader for a program
 * @param   prog    program to use
 * @param   sh      shader to set
 */
void cgl_shader_program_set_fragment_shader(struct cgl_shader_program *prog, struct cgl_shader *sh)
{
    prog->f_shader = sh;
}

/**
 * sets the geometry shader for a program
 * @param   prog    program to use
 * @param   sh      shader to set
 */
void cgl_shader_program_set_geometry_shader(struct cgl_shader_program *prog, struct cgl_shader *sh)
{
    prog->g_shader = sh;
}

/**
 * sets the program to be the currently running program
 * @param   prog    program to use
 */
void cgl_shader_program_use(struct cgl_shader_program *prog)
{
    glUseProgram(cgl_object_get_ID((struct cgl_object *)prog));
}

/**
 * links the shaders used by a program
 * @param   prog    program to use
 * @return  error code
 */
int cgl_shader_program_link(struct cgl_shader_program *prog)
{
    int err = 0;

    cgl_object_set_ID((struct cgl_object *)prog, glCreateProgram());

    if (prog->v_shader && cgl_shader_check_flag(prog->v_shader, cgl_shader_flag_compiled))
    {
        glAttachShader(cgl_object_get_ID((struct cgl_object *)prog),
                       cgl_object_get_ID((struct cgl_object *)(prog->v_shader)));
    }

    if (prog->f_shader && cgl_shader_check_flag(prog->f_shader, cgl_shader_flag_compiled))
    {
        glAttachShader(cgl_object_get_ID((struct cgl_object *)prog),
                       cgl_object_get_ID((struct cgl_object *)(prog->f_shader)));
    }

    if (prog->g_shader && cgl_shader_check_flag(prog->g_shader, cgl_shader_flag_compiled))
    {
        glAttachShader(cgl_object_get_ID((struct cgl_object *)prog),
                       cgl_object_get_ID((struct cgl_object *)(prog->g_shader)));
    }

    glLinkProgram(cgl_object_get_ID((struct cgl_object *)prog));

    err = check_link_status(cgl_object_get_ID((struct cgl_object *)prog));

    if (err != 0)
    {
        err = cgl_error_shader_program_linking;
    }

    return err;
}

/**
 * frees the given cgl_shader_program
 * @param   sh     shader_program to free
 */
void cgl_shader_program_delete(struct cgl_shader_program *prog)
{
}

/**
 * check linking status for a program
 * @param   ID      program ID
 * @return 0 = OK, 1 = errors
 */
static int check_link_status(unsigned int ID)
{
    int success = 0;

    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success)
    {
        return 1;
    }

    return 0;
}