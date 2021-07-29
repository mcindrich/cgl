#include <cgl/object.h>
#include <cgl/texture2D.h>
#include <GL/glew.h>

/**
 * initializes the 2D texture struct
 * @param   tex     texture to init
 */
void cgl_texture2D_init(struct cgl_texture2D *tex)
{
    cgl_object_init((struct cgl_object *)tex);
}

/**
 * generates a texture object using a given image
 * @param   tex     texture to use
 * @param   img     image to use
 * @param   fmt     format of the image - GL_RGB
 * @param   ifmt    internal format of the image data
 * @return  error code - 0 on success
 */
int cgl_texture2D_gen(struct cgl_texture2D *tex, struct cgl_image *img, unsigned int fmt, unsigned int ifmt)
{
    int err = 0;
    unsigned int tmp;
    glGenTextures(1, &tmp);

    cgl_object_set_ID((struct cgl_object *)tex, tmp);
    glBindTexture(GL_TEXTURE_2D, cgl_object_get_ID((struct cgl_object *)tex));
    glTexImage2D(GL_TEXTURE_2D, 0, fmt, img->w, img->h, 0, ifmt, GL_UNSIGNED_BYTE, img->pix);
    glGenerateMipmap(GL_TEXTURE_2D);

    // unbind current tex
    glBindTexture(GL_TEXTURE_2D, 0);

    return err;
}

/**
 * frees the given texture
 * @param   tex     texture to free
 */
void cgl_texture2D_free(struct cgl_texture2D *tex)
{
}