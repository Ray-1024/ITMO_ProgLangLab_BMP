#include "image/formats/bmp/bmp24/bmp24.h"
#include <stdio.h>

inline static enum bmp_read_status
bmp_read_header_from_file(FILE *file, struct bmp_header *header) {
    if (header == NULL)return BMP_READ_INVALID_HEADER;
    if (header->biHeight < 0 || header->biWidth < 0 || fread(header, sizeof(struct bmp_header), 1, file) != 1)
        return BMP_READ_INVALID_SIGNATURE;
    return BMP_READ_OK;
}

inline static enum bmp_read_status
bmp_read_pixels_from_file(FILE *file, struct image *image) {
    int32_t tmpBuffer;
    size_t buff_size = 4 - (image->w * sizeof(struct pixel)) % 4;
    for (size_t i = 0; i < image->h; ++i) {
        if (fread(image->data + image->w * i, sizeof(struct pixel), image->w, file) != image->w)
            return BMP_READ_INVALID_BITS;
        if (buff_size != 0 && fread(&tmpBuffer, buff_size, 1, file) != 1)
            return BMP_READ_INVALID_BITS;
    }
    return BMP_READ_OK;
}

static enum bmp_read_status bmp24_read_from_opened_file(FILE *file, struct image *image) {
    struct bmp_header header;
    enum bmp_read_status status = bmp_read_header_from_file(file, &header);
    if (status != BMP_READ_OK)return status;
    *image = image_create(header.biWidth, header.biHeight);
    return bmp_read_pixels_from_file(file, image);
}

enum bmp_read_status bmp24_read_from_file(const char *filename, struct image *img) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL)return BMP_READ_INVALID_SIGNATURE;
    enum bmp_read_status status = bmp24_read_from_opened_file(file, img);
    fclose(file);
    return status;
}

static struct bmp_header create_default_header(const struct image image) {
    struct bmp_header header = {0};
    header.bfType = 19778;
    header.bfileSize = sizeof(struct bmp_header) + (((image.w * sizeof(struct pixel) + 3) >> 2) << 2) * image.h;
    header.bOffBits = sizeof(struct bmp_header);
    header.biSize = 40;
    header.biWidth = image.w;
    header.biHeight = image.h;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biSizeImage = header.bfileSize - header.bOffBits;
    header.biXPelsPerMeter = 3780;
    header.biYPelsPerMeter = 3780;
    return header;
}


inline static enum bmp_write_status bmp_write_header_to_file(FILE *file, const struct image image) {
    struct bmp_header header = create_default_header(image);
    if (fwrite(&header, sizeof(struct bmp_header), 1, file) != 1)
        return BMP_WRITE_ERROR;
    return BMP_WRITE_OK;
}

inline static enum bmp_write_status bmp_write_pixels_to_file(FILE *file, const struct image image) {
    int32_t tmpBuffer = 0;
    size_t buff_size = 4 - (image.w * sizeof(struct pixel)) % 4;
    for (uint64_t row = 0; row < image.h; ++row) {
        if (fwrite(image.data + image.w * row, sizeof(struct pixel), image.w, file) != image.w)
            return BMP_WRITE_ERROR;
        if (buff_size != 0 && fwrite(&tmpBuffer, buff_size, 1, file) != 1)
            return BMP_WRITE_ERROR;
    }
    return BMP_WRITE_OK;
}


static enum bmp_write_status bmp24_write_to_opened_file(FILE *out, const struct image img) {
    if (out == NULL)return BMP_WRITE_ERROR;
    enum bmp_write_status status = bmp_write_header_to_file(out, img);
    if (status != BMP_WRITE_OK)return status;
    return bmp_write_pixels_to_file(out, img);
}


enum bmp_write_status bmp24_write_to_file(const char *filename, struct image img) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL)return BMP_WRITE_ERROR;
    enum bmp_write_status status = bmp24_write_to_opened_file(file, img);
    fclose(file);
    return status;
}
