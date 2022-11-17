#ifndef IMAGE_TRANSFORMER_IMAGE_H
#define IMAGE_TRANSFORMER_IMAGE_H

#include <stdint.h>

#pragma pack(push, 1)
struct pixel {
    uint8_t b, g, r;
};
#pragma pack(pop)

struct image {
    uint64_t w, h;
    struct pixel *data;
};

typedef uint32_t (*image_read_from_file)(const char *filename, struct image *img);

typedef uint32_t (*image_write_to_file)(const char *filename, const struct image img);


struct image image_create(uint64_t width, uint64_t height);

struct pixel image_get_pixel(struct image image, uint64_t row, uint64_t column);

void image_set_pixel(struct image image, uint64_t row, uint64_t column, struct pixel newPixel);


void image_free(struct image image);


#endif
