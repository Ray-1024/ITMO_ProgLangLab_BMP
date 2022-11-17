#ifndef IMAGE_TRANSFORMER_BMP_H
#define IMAGE_TRANSFORMER_BMP_H

#include <stdint.h>

#pragma pack(push, 1)
struct bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

enum bmp_read_status {
    BMP_READ_OK = 0,
    BMP_READ_INVALID_SIGNATURE,
    BMP_READ_INVALID_BITS,
    BMP_READ_INVALID_HEADER
};

enum bmp_write_status {
    BMP_WRITE_OK = 0,
    BMP_WRITE_ERROR
};

#endif
