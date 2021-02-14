//
// Created by kurt on 22.01.2021.
//
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include "list.h"
#include "list_io.h"
#include "maybe_int.h"
#include "io.h"

int64_t check_file(FILE* file) {
    if (errno || ferror(file)) {
        fclose(file);
        return 0;
    } else return 1;
}
int64_t close_file(FILE* file) {
    fclose(file);
    if (errno) return 0;
    else return 1;
}
FILE* open_file(const char* filename, const char* mode) {
    errno = 0;
    FILE* file = fopen(filename, mode);
    if (errno) return NULL;
    else return file;
}


bool save(const struct list* lst, const char* filename){
    FILE* file=open_file(filename,"w");
    if(file==NULL) return 0;
    struct list* list=node_create(lst->value);
    list->next=lst->next;
    while (list->next){
        fprintf(file,"% " PRId64,list->value);
        list=list->next;
    }
    fprintf(file,"% " PRId64,list->value);

    return fclose(file);
}
bool load(struct list** lst, const char* filename){
    FILE* file=open_file(filename,"r");
    if(file==NULL) return 0;
    int64_t val;
    while(true){
        fscanf(file,"%" SCNd64,&val);
        list_add_front(lst,val);
        if (feof(file)) break;
        if (!check_file(file)) return 0;
    }
    *lst=list_reverse(*lst);
    return fclose(file);
}
bool serialize(const struct list* lst, const char* filename){
    FILE* file = open_file(filename, "w");
    if (file == NULL) return 0;
    struct list* list=node_create(lst->value);
    list->next=lst->next;
    while (list->next){
        fwrite(&list->value,sizeof(list->value),1,file);
        if (!check_file(file)) return 0;
        list=list->next;
    }
    fwrite(&list->value,sizeof(list->value),1,file);
    return close_file(file);
}
bool deserialize(struct list** lst, const char* filename){
    FILE* file=open_file(filename,"r");
    if(file==NULL) return 0;
    int64_t val;
    while (true){
        fread(&val, sizeof(int64_t), 1, file);
        if (feof(file)) break;
        if (!check_file(file)) return 0;
        list_add_front(lst,val);
    }
    *lst=list_reverse(*lst);
    return fclose(file);
}
struct list* list_read() {
    int64_t val;
    struct list* new_list = NULL;
    puts("Enter list:");

    while(scanf("%" SCNd64, &val) == 1) {
         list_add_front( &new_list,val);
    }
    new_list=list_reverse(new_list);
    return new_list;
}
