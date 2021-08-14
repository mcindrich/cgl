#ifndef CGL_TEXTURE_2D_H
#define CGL_TEXTURE_2D_H

#include <cgl/object.h>
#include <cgl/image.h>

struct cgl_texture2D
{
    struct cgl_object obj;
};

/**
 * initializes the 2D texture struct
 * @param   tex     texture to init
 */
void cgl_texture2D_init(struct cgl_texture2D *tex);

/**
 * generates a texture object using a given image
 * @param   tex     texture to use
 * @param   img     image to use
 * @param   fmt     format of the image - GL_RGB
 * @param   ifmt    internal format of the image data
 * @return  error code - 0 on success
 */
int cgl_texture2D_gen(struct cgl_texture2D *tex, struct cgl_image *img, unsigned int fmt, unsigned int ifmt);

/**
 * binds the given texture object to GL_TEXTURE_2D
 * @param   tex     texture to use
 */
void cgl_texture2D_bind(struct cgl_texture2D *tex);

/**
 * unbinds object bound to GL_TEXTURE_2D
 */
void cgl_texture2D_unbind(void);

/**
 * frees the given texture
 * @param   tex     texture to free
 */
void cgl_texture2D_delete(struct cgl_texture2D *tex);

#endif // CGL_TEXTURE_2D_H
