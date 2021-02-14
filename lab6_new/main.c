#include <stdio.h>
#include "bmp.h"
#include "util.h"
#include "errors_util.h"
#include "image.h"
#include <malloc.h>
int main() {
    char* in_name="jojo.bmp";
    FILE* in_file=open_file(in_name,"rb");
    struct bmp_header* bmpHeader=malloc(sizeof(struct bmp_header));
    read_bmp_header(bmpHeader,in_file);
    uint32_t* colours=malloc(bmpHeader->bOffBits-54);
    read_colour_table(colours,in_file,bmpHeader);
    uint32_t width=bmpHeader->biWidth;
    uint32_t height=bmpHeader->biHeight;
    struct pixel* pixels= malloc(sizeof(uint8_t)*3*height*width);
    read_pixels(pixels,in_file,bmpHeader);
    close_file(in_file);


    struct image* image=malloc(sizeof(uint32_t)*2+ sizeof(uint8_t)*3*height*width);
    image->width=width;
    image->height=height;
    image->data=pixels;


    char* out_name="jojoW.bmp";
    FILE* out_file=open_file(out_name,"wb");
    image=rotate(image);
    bmpHeader->biWidth=image->width;
    bmpHeader->biHeight=image->height;
    write_header(bmpHeader,out_file);
    write_colour_table(colours,out_file,bmpHeader);
    write_pixels(image->data,out_file,bmpHeader);
    close_file(out_file);
    free(image);
    free(bmpHeader);
    free(pixels);
    free(colours);

    return 0;
}
