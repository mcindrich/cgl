#include <cgl/common.h>
#include <cgl/object.h>
#include <stdlib.h>
#include <string.h>

/** represents an OpenGL object - unsigned int as an ID */
struct cgl_object
{
    unsigned int ID;
};

/**
 * creates a new cgl_object struct
 * @return  newly allocated object
 */
struct cgl_object *cgl_object_new()
{
    struct cgl_object *obj = NULL;

    obj = (struct cgl_object *)malloc(sizeof(struct cgl_object));
    if (!obj)
    {
        return NULL;
    }
    obj->ID = 0;

    return obj;
}

/**
 * initializes the object structure
 * @param   obj     object to initialize
 */
void cgl_object_init(struct cgl_object *obj)
{
    obj->ID = 0;
}

/**
 * sets the opengl object ID
 * @param   obj     object to use
 * @param   ID      ID to set
 */
void cgl_object_set_ID(struct cgl_object *obj, unsigned int ID)
{
    obj->ID = ID;
}

/**
 * returns the ID of an object
 * @param   obj     object to use
 * @return  ID of an object
 */
const unsigned int cgl_object_get_ID(struct cgl_object *obj)
{
    return obj->ID;
}