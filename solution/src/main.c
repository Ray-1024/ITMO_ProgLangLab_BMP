#include "image/formats/bmp/bmp24/bmp24.h"
#include "image/transformations/rotate/rotate.h"
#include "image/utils/utils.h"
#include <stdio.h>

int main(int argc, char **argv) {
    (void) argc;
    (void) argv; // suppress 'unused parameters' warning
    if (argc > 2)
        read_transform_write(bmp24_read_from_file, rotate,
                             bmp24_write_to_file, argv[1], argv[2]);
    else
        printf("[I WANT MORE ARGUMENTS]");
    return 0;
}
