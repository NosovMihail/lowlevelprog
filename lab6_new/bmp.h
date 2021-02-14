//
// Created by kurt on 28.01.2021.
//

#ifndef LAB6_NEW_BMP_H
#define LAB6_NEW_BMP_H
#include "errors_util.h"
#include <inttypes.h>
#include <stdio.h>
#include "util.h"
#include "image.h"
struct bmp_header{
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
enum read_status read_bmp_header(struct bmp_header* bmpHeader,FILE* bmp_file);
enum read_status read_colour_table(uint32_t* colours,FILE* bmp_file,struct bmp_header* bmpHeader);
enum read_status read_pixels(struct pixel* pixels,FILE* bmp_file,struct bmp_header* bmpHeader);
enum write_status write_header(struct bmp_header* bmpHeader,FILE* bmp_file);
enum write_status write_colour_table(uint32_t* colours,FILE* bmp_file,struct bmp_header* bmpHeader);
enum write_status write_pixels(struct pixel* pixels,FILE* bmp_file,struct bmp_header* bmpHeader);

#endif //LAB6_NEW_BMP_H
