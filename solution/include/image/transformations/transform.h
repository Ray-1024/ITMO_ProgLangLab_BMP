#ifndef IMAGE_TRANSFORMER_TRANSFORM_H
#define IMAGE_TRANSFORMER_TRANSFORM_H

#include "image/image.h"

enum transform_status {
    TRANSFORM_OK,
    TRANSFORM_ERROR
};

typedef enum transform_status (*image_transform)(struct image from, struct image *to);

#endif
