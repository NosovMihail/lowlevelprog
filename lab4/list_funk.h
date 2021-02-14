#ifndef lf
#define lf
#include "list_funk.c"
#endif
void list_print(const struct list* l);
void list_add_front( struct list** old, int64_t value );
struct list* list_last( struct list* list );
void list_add_back( struct list** old, int64_t value );
size_t list_length( struct list const* list );
struct list* list_node_at( struct list* list, size_t idx );
struct maybe_int64 list_at(struct list* list,size_t idx);
struct maybe_int64 list_sum( struct list const* list );
struct list* list_reverse( const struct list* list );
struct list* list_read();