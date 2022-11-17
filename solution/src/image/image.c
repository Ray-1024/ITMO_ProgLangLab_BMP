#include "image/image.h"
#include <malloc.h>

struct pixel image_get_pixel(const struct image image, uint64_t row, uint64_t column) {
    return image.data[row * image.w + column];
}

void image_set_pixel(struct image image, uint64_t row, uint64_t column, struct pixel newPixel) {
    image.data[row * image.w + column] = newPixel;
}

struct image image_create(uint64_t width, uint64_t height) {
    return (struct image) {.w=width, .h=height, .data=malloc(width * height * sizeof(struct pixel))};
}

void image_free(struct image image) {
    free(image.data);
}
