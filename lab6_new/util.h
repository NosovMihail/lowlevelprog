//
// Created by kurt on 28.01.2021.
//

#ifndef LAB6_NEW_UTIL_H
#define LAB6_NEW_UTIL_H
#include <errno.h>
#include "errors_util.h"
#include <stdio.h>
#include <inttypes.h>
FILE* open_file(const char* filename, const char* mode);
int64_t close_file(FILE* file);
int64_t check_file(FILE* file);
enum read_status read_uint8(uint8_t *num,FILE *in);
enum read_status read_uint16(uint16_t *num,FILE *in);
enum read_status read_uint32(uint32_t *num,FILE *in);
enum write_status write_uint8(uint8_t *num,FILE *in);
enum write_status write_uint16(uint16_t *num,FILE *in);
enum write_status write_uint32(uint32_t *num,FILE *in);
#endif //LAB6_NEW_UTIL_H
