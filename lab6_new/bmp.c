//
// Created by kurt on 28.01.2021.
//
#include "bmp.h"
#include "errors_util.h"
#include <stdio.h>
#include "util.h"
#include "image.h"
enum read_status read_bmp_header(struct bmp_header* bmpHeader,FILE* bmp_file){
    read_uint16(&bmpHeader->bfType,bmp_file);
    read_uint32(&bmpHeader->bfileSize,bmp_file);
    read_uint32(&bmpHeader->bfReserved,bmp_file);
    read_uint32(&bmpHeader->bOffBits,bmp_file);
    read_uint32(&bmpHeader->biSize,bmp_file);
    read_uint32(&bmpHeader->biWidth,bmp_file);
    read_uint32(&bmpHeader->biHeight,bmp_file);
    read_uint16(&bmpHeader->biPlanes,bmp_file);
    read_uint16(&bmpHeader->biBitCount,bmp_file);
    read_uint32(&bmpHeader->biCompression,bmp_file);
    read_uint32(&bmpHeader->biSizeImage,bmp_file);
    read_uint32(&bmpHeader->biXPelsPerMeter,bmp_file);
    read_uint32(&bmpHeader->biYPelsPerMeter,bmp_file);
    read_uint32(&bmpHeader->biClrUsed,bmp_file);
    read_uint32(&bmpHeader->biClrImportant,bmp_file);
    return READ_OK;
}
enum read_status read_colour_table(uint32_t* colours,FILE* bmp_file,struct bmp_header* bmpHeader){
    for(size_t i=0;i<(bmpHeader->bOffBits-54)/4;i++){
        read_uint32(&colours[i],bmp_file);
    }
    return READ_OK;
}
enum read_status read_pixels(struct pixel* pixels,FILE* bmp_file,struct bmp_header* bmpHeader){
    size_t width=bmpHeader->biWidth;
    size_t height=bmpHeader->biHeight;
    uint8_t trash=0;
    for(size_t i=0;i<height;i++){
        for(size_t j=0;j<width;j++){
            read_uint8(&pixels[i*width+j].b,bmp_file);
            read_uint8(&pixels[i*width+j].g,bmp_file);
            read_uint8(&pixels[i*width+j].r,bmp_file);
            read_uint8(&trash,bmp_file);
        }
    }
    return READ_OK;
}
enum write_status write_header(struct bmp_header* bmpHeader,FILE* bmp_file){
    write_uint16(&bmpHeader->bfType,bmp_file);
    write_uint32(&bmpHeader->bfileSize,bmp_file);
    write_uint32(&bmpHeader->bfReserved,bmp_file);
    write_uint32(&bmpHeader->bOffBits,bmp_file);
    write_uint32(&bmpHeader->biSize,bmp_file);
    write_uint32(&bmpHeader->biWidth,bmp_file);
    write_uint32(&bmpHeader->biHeight,bmp_file);
    write_uint16(&bmpHeader->biPlanes,bmp_file);
    write_uint16(&bmpHeader->biBitCount,bmp_file);
    write_uint32(&bmpHeader->biCompression,bmp_file);
    write_uint32(&bmpHeader->biSizeImage,bmp_file);
    write_uint32(&bmpHeader->biXPelsPerMeter,bmp_file);
    write_uint32(&bmpHeader->biYPelsPerMeter,bmp_file);
    write_uint32(&bmpHeader->biClrUsed,bmp_file);
    write_uint32(&bmpHeader->biClrImportant,bmp_file);
    return WRITE_OK;
}
enum write_status write_colour_table(uint32_t* colours,FILE* bmp_file,struct bmp_header* bmpHeader){
    for(size_t i=0;i<(bmpHeader->bOffBits-54)/4;i++){
        write_uint32(&colours[i],bmp_file);
    }
    return WRITE_OK;
}
enum write_status write_pixels(struct pixel* pixels,FILE* bmp_file,struct bmp_header* bmpHeader){
    size_t width=bmpHeader->biWidth;
    size_t height=bmpHeader->biHeight;
    uint8_t trash=255;
    for(size_t i=0;i<height;i++){
        for(size_t j=0;j<width;j++){
            write_uint8(&pixels[i*width+j].b,bmp_file);
            write_uint8(&pixels[i*width+j].g,bmp_file);
            write_uint8(&pixels[i*width+j].r,bmp_file);
            write_uint8(&trash,bmp_file);
        }
    }
    return WRITE_OK;
}







