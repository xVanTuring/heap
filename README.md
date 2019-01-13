# Priority Queue

## LICENSE
### Source code based on leptonica, with a few modifications.

## Usage
``` c
#include "heap.h"
struct struct_a
{
	size_t sort_param; // can be any name, but the type must be size_t, and at the first
	int value;
};

HEAP* heap = heap_create(0, SORT_DECREASING);
struct struct_a* a = malloc(sizeof(struct struct_a));
a->sort_param = 190;
heap_add(heap, a);
struct struct_a* item = heap_remove(heap); // pop the bigger/smaller
```