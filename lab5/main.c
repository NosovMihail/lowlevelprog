#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include "io.h"
#include "list.h"
#include "list_io.h"



// --- начало решения на Stepik ---

/* Запустить функцию f на каждом элементе списка  */
void list_foreach(const struct list * l, void (f)(int64_t)) {
  f(l->value);
  while(l->next){
      l=l->next;
      f(l->value);
  }

}

/* Изменить каждый элемент списка с помощью функции f  */
void list_map_mut( struct list  * l, int64_t (f) (int64_t)) {
    l->value=f(l->value);
    while(l->next){
        l=l->next;
        l->value=f(l->value);
    }
}

/*  Создать новый список, в котором каждый элемент получен из соответствующего
 элемента списка l путём применения функции f */
struct list* list_map( const struct list* l, int64_t (f) (int64_t)) {
    struct list* list=node_create(f(l->value));
    while(l->next){
        l=l->next;
        list_add_back(&list,f(l->value));
    }
    return list;
}

/* Свернуть список l с помощью функции f. */
int64_t list_fold(const struct list* l, int64_t init, int64_t (f)(int64_t, int64_t)) {
    int64_t result=init;
    result=f(result,l->value);
    while(l->next){
        l=l->next;
        result=f(result,l->value);
    }
    return result;
}

/*  Сгенерировать список длины sz с помощью значения init и функции f
 Результат: init, f(init), f(f(init)), ... */
struct list* list_iterate( int64_t init, size_t sz, int64_t f(int64_t) ) {
    struct list* list=node_create(init);
    for(size_t i=0;i<sz-1;i++){
        init=f(init);
        list_add_back(&list,init);
    }
    return list;
}

// --- конец решения на Stepik ---

void print_int64_space(int64_t i) { print_int64( i ); printf(" "); }
static int64_t triple( int64_t x ) { return x * 3; }
static int64_t square( int64_t x ) { return x * x; }
static int64_t sum( int64_t x, int64_t y) { return x + y; }

int main() {
  struct list* l1 =list_read();
  struct list const* l1c = l1;

  printf("list : ");
  list_foreach( l1c, print_int64_space);
  print_newline();

  printf("(list *3)^2: ");
  struct list* l2 = list_map( l1c, triple);

  list_map_mut( l2, square);
  struct list const* l2c = l2;

  list_foreach( l2c, print_int64_space);
  print_newline();

  printf("list fold: ");
  print_int64( list_fold( l2c, 0, sum));
  print_newline();

  printf("list iterate: ");
  struct  list* l3 = list_iterate( 7, 10, triple);
  struct  list const* l3c = l3;
  list_foreach( l3c, print_int64_space);
  print_newline();

  char file_txt[] = "test.txt";
  char file_bin[] = "test.bin";
  save(l1,file_txt);
  struct list* l4={0};
  struct list* l5={0};

  printf("list load: ");
  load(&l4,file_txt);
  list_print(l4);
  print_newline();
  serialize(l1,file_bin);

  printf("deserialize: ");
  deserialize(&l5,file_bin);
  list_print(l5);
  print_newline();

  list_destroy( l1 );
  list_destroy( l2 );
  list_destroy( l3 );
  list_destroy( l4 );
  list_destroy( l5 );
  return 0;
}

