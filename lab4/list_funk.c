#include <malloc.h>
#include <stdio.h>
#include "subsidiary_funk.h"
struct list {
    int64_t value;
    struct list* next;
};

struct list* node_create( int64_t value ) {
    struct list* const list = malloc( sizeof( struct list ) );
    *list = (struct list) { .value = value, .next = NULL };
    return list;
}
// Вывести список
void list_print(const struct list* l) {
    while (l) {
        printf("%" PRId64 " ", l->value);
        l = l->next;
    }
}
// Освободить память под весь список
void list_destroy( struct list* list_d ) {
    while(list_d){
        struct list* tmp=list_d->next;
        free(list_d);
        list_d=tmp;
    }
}

// добавить элемент в начало списка
// необходимо передавать указатель на указатель, т.к.
// список задаётся указателем на первый элемент
// Добавление элемента в начало это перенаправление
// указателя на свежий элемент.
void list_add_front( struct list** old, int64_t value ) {
    struct list *tmp=malloc(sizeof(struct list));
    tmp->value=value;
    tmp->next=*old;
    *old=tmp;
}


// Последний элемент списка
struct list* list_last( struct list* list ) {
    struct list* tmp=list;
    while(tmp->next){
        tmp=tmp->next;
    }
    return tmp;
}


// Добавить элемент в конец
// Используйте list_last
void list_add_back( struct list** old, int64_t value ) {
    struct list *tmp=malloc(sizeof(struct list));
    tmp->next=NULL;
    tmp->value=value;
    list_last(*old)->next=tmp;
}

// Посчитать длину списка
size_t list_length( struct list const* list ) {
    size_t size=1;
    struct list* tmp=list->next;
    while(tmp){
        size++;
        tmp=tmp->next;
    }
    return size;
}

// указатель на структуру по индексу или NULL
struct list* list_node_at( struct list* list, size_t idx ) {
    struct list* tmp=list;
    for(size_t i=0;i<idx;i++){
        if(tmp->next==NULL) return NULL;
        tmp=tmp->next;
    }
    return tmp;
}

// Вернуть элемент по индексу или none_int64 если индекс слишком большой
struct maybe_int64 list_at(struct list* list,size_t idx) {
    struct list* tmp=list_node_at(list,idx);
    if(tmp==NULL) return none_int64;

    else return some_int64(tmp->value);
}


// Сумма элементов в списке
struct maybe_int64 list_sum( struct list const* list ) {
    int64_t sum=list->value;
    struct list* tmp=list->next;
    while(tmp){
        sum+=tmp->value;
        tmp=tmp->next;
    }
    return some_int64(sum);
}


// Возвращает перевернутую копию списка
struct list* list_reverse( const struct list* list ) {
    struct list *tmp=list->next;
    struct list *list1=malloc( sizeof( struct list ) );
    list1->next=NULL;
    list1->value=list->value;
    while (tmp->next){
        list_add_front(&list1,tmp->value);
        tmp=tmp->next;
    }
    list_add_front(&list1,tmp->value);

    return list1;
}


// Прочитать список со входа
struct list* list_read() {
    struct list* l;
    for (;;) {
        const struct maybe_int64 i = read_int64();

        if (i.valid) {
            list_add_front( &l, i.value );
        }
        else {
            break;
        }
    }
    struct list* rev = list_reverse( l );
    list_destroy( l );
    return rev;
}

