//
// Created by kurt on 28.01.2021.
//
#include <inttypes.h>
#include "image.h"
#include <malloc.h>
struct image* rotate( const struct image* source ){
    struct image* new_image=malloc(sizeof(uint32_t)*2+ sizeof(uint8_t)*3*source->height*source->width);
    struct pixel* pixels= malloc(sizeof(uint8_t)*3*source->height*source->width);
    new_image->width=source->height;
    new_image->height=source->width;
    uint32_t count=1;
    uint32_t count2=0;
    for(size_t i=0;i<source->height*source->width;i++){
       pixels[i]=source->data[(source->width)*count++-1-count2];
        if(count==source->height+1){
            count=1;
            count2++;
        }
    }
    new_image->data=pixels;
    return new_image;
}