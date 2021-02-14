//
// Created by kurt on 23.01.2021.
//

#ifndef LAB5_LIST_IO_H
#define LAB5_LIST_IO_H
#include <stdbool.h>
#include <errno.h>
#include "list.h"
bool save(const struct list* lst, const char* filename);
bool load(struct list** lst, const char* filename);
bool serialize(const struct list* lst, const char* filename);
bool deserialize(struct list** lst, const char* filename);
struct list* list_read();
#endif //LAB5_LIST_IO_H

