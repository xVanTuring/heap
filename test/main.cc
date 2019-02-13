#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

struct struct_a {
  float sort_param;
  int value;
};

int main() {
  HEAP *heap = heap_create(0, SORT_DECREASING);
  struct struct_a *a = (struct struct_a *)malloc(sizeof(struct struct_a));
  struct struct_a *b = (struct struct_a *)malloc(sizeof(struct struct_a));
  struct struct_a *c = (struct struct_a *)malloc(sizeof(struct struct_a));
  struct struct_a *d = (struct struct_a *)malloc(sizeof(struct struct_a));
  a->sort_param = 190;
  b->sort_param = 10;
  c->sort_param = 70;
  d->sort_param = 30;
  heap_add(heap, a);
  heap_add(heap, b);
  heap_add(heap, c);
  heap_add(heap, d);
  const int size = 4;
  int data[] = {190, 70, 30, 10};
  for (int i = 0; i < size; ++i) {
    struct struct_a *item = (struct struct_a *)heap_remove(heap);
    // const int compared = item->sort_param == data[i];
    printf("Pop %f equals to %d \n", item->sort_param, data[i]);
  }

  heap_destroy(&heap, TRUE);
  return 0;
}
