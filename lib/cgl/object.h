#ifndef CGL_OBJECT_H
#define CGL_OBJECT_H

struct cgl_object;

/**
 * initializes the object structure
 * @param   obj     object to initialize
 */
void cgl_object_init(struct cgl_object *obj);

/**
 * sets the opengl object ID
 * @param   obj     object to use
 * @param   ID      ID to set
 */
void cgl_object_set_ID(struct cgl_object *obj, unsigned int ID);

/**
 * returns the ID of an object
 * @param   obj     object to use
 * @return  ID of an object
 */
const unsigned int cgl_object_get_ID(struct cgl_object *obj);

#endif // CGL_OBJECT_H