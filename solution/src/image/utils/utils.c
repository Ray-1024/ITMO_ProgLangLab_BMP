#include "image/formats/bmp/bmp.h"
#include "image/utils/utils.h"
#include <stdio.h>

void
read_transform_write(image_read_from_file read, image_transform transform, image_write_to_file write, const char *from,
                     const char *to) {
    struct image img, mod_img;
    if (read(from, &img) != BMP_READ_OK)printf("[READ ERROR]\n");
    if (transform(img, &mod_img) != TRANSFORM_OK)printf("[TRANSFORM ERROR]\n");
    image_free(img);
    if (write(to, mod_img) != BMP_WRITE_OK)printf("[WRITE ERROR]\n");
    image_free(mod_img);
}
