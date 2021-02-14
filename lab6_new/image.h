//
// Created by kurt on 28.01.2021.
//

#ifndef LAB6_NEW_IMAGE_H
#define LAB6_NEW_IMAGE_H
#include <inttypes.h>
struct image {
    uint64_t width, height;
    struct pixel* data;
};
struct pixel {
    uint8_t b, g, r;
};
struct image* rotate( const struct image* source );
#endif //LAB6_NEW_IMAGE_H
