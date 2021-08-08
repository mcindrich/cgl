#include <cgl/image.h>
#include <stb/stb_image.h>

/**
 * initializes the helper image struct
 * @param   img     image struct to init
 */
void cgl_image_init(struct cgl_image *img)
{
    img->w = img->h = img->nr_ch = 0;
    img->pix = NULL;
}

/**
 * attempts to load an image from a given path
 * @param   img     image struct to use
 * @param   path    path of the image to load
 * @return error code - 0 on success
 */
int cgl_image_load(struct cgl_image *img, const char *path)
{
    img->pix = stbi_load(path, &img->w, &img->h, &img->nr_ch, 0);
    return img->pix == NULL;
}

/**
 * frees the helper image struct
 * @param   img     image struct to free
 */
void cgl_image_delete(struct cgl_image *img)
{
    if (img->pix)
    {
        stbi_image_free(img->pix);
    }
    cgl_image_init(img);
}
