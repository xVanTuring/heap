#ifndef HEAP_H
#define HEAP_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

#define SWAP_ITEMS(i, j)       { void *tempitem = heap->array[(i)]; \
                                 heap->array[(i)] = heap->array[(j)]; \
                                 heap->array[(j)] = tempitem; }

struct Heap
{
	int nalloc;
	int n;
	void** array;
	int direction;
};

typedef struct Heap HEAP;
static const int MIN_BUFFER_SIZE = 20;
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern HEAP* heap_create(int nalloc, int direction);

extern void heap_destroy(HEAP** pheap, int freeflag);

extern int heap_add(HEAP* heap, void* item);

extern void* heap_remove(HEAP* heap);

extern int heap_swap_up(HEAP* heap, int index);

extern int heap_swap_down(HEAP* heap);

extern int heap_get_count(HEAP* heap);

extern int heap_sort(HEAP* heap);

extern int heap_sort_strict_order(HEAP* heap);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // !HEAP_H
