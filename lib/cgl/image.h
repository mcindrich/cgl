#ifndef CGL_IMAGE_H
#define CGL_IMAGE_H

struct cgl_image
{
    int w;
    int h;
    int nr_ch;
    unsigned char *pix;
};

/**
 * initializes the helper image struct
 * @param   img     image struct to init
 */
void cgl_image_init(struct cgl_image *img);

/**
 * attempts to load an image from a given path
 * @param   img     image struct to use
 * @param   path    path of the image to load
 * @return error code - 0 on success
 */
int cgl_image_load(struct cgl_image *img, const char *path);

/**
 * frees the helper image struct
 * @param   img     image struct to free
 */
void cgl_image_free(struct cgl_image *img);

#endif // CGL_IMAGE_H