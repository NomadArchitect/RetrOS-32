#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>

typedef unsigned char* bitmap_t;

void set_bitmap(bitmap_t b, int i);
void unset_bitmap(bitmap_t b, int i);
bitmap_t create_bitmap(int n);
int get_free_bitmap(bitmap_t b, int n);

void destroy_bitmap(bitmap_t b);
int get_bitmap_size(int n);

#endif /* BITMAP_H */
