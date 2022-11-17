file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    src/*.c
    src/*.h
    include/*.h
)

add_executable(image-transformer ${sources} src/image/image.c include/image/image.h src/image/formats/bmp/bmp24/bmp24.c include/image/formats/bmp/bmp24/bmp24.h src/image/transformations/rotate/rotate.c include/image/transformations/rotate/rotate.h include/image/utils/utils.h include/image/transformations/transform.h include/image/formats/bmp/bmp.h src/image/utils/utils.c)
target_include_directories(image-transformer PRIVATE src include)
