//
// Created by kurt on 28.01.2021.
//
#include <inttypes.h>
#include <stdio.h>
#include "errors_util.h"
#include <errno.h>
int64_t check_file(FILE* file) {
    if (errno || ferror(file)) {
    fclose(file);
    return 0;
    } else return 1;
}
FILE* open_file(const char* filename, const char* mode) {
    errno = 0;
    FILE* file = fopen(filename, mode);
    if (errno) return NULL;
    else return file;
}
int64_t close_file(FILE* file) {
    fclose(file);
    if (errno) return 0;
    else return 1;
}
enum read_status read_uint8(uint8_t *num,FILE *in){
    if (!check_file(in)) return  READ_ERROR;
    fread(num, sizeof(uint8_t),1,in);
    return READ_OK;
}
enum read_status read_uint16(uint16_t *num,FILE *in){
    if (!check_file(in)) return  READ_ERROR;
    fread(num, sizeof(uint16_t),1,in);
    return READ_OK;
}
enum read_status read_uint32(uint32_t *num,FILE *in) {
    if (!check_file(in)) return READ_ERROR;
    fread(num, sizeof(uint32_t), 1, in);
    return READ_OK;
}
enum write_status write_uint8(uint8_t *num,FILE *in){
    if (!check_file(in)) return WRITE_ERROR;
    fwrite(num, sizeof(uint8_t), 1, in);
    return WRITE_OK;
}
enum write_status write_uint16(uint16_t *num,FILE *in){
    if (!check_file(in)) return WRITE_ERROR;
    fwrite(num, sizeof(uint16_t), 1, in);
    return WRITE_OK;
}
enum write_status write_uint32(uint32_t *num,FILE *in){
    if (!check_file(in)) return WRITE_ERROR;
    fwrite(num, sizeof(uint32_t), 1, in);
    return WRITE_OK;
}