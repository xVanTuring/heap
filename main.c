#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

struct struct_a
{
	float sort_param;
	int value;
};

int main()
{
	HEAP* heap = heap_create(0, SORT_DECREASING);
	struct struct_a* a = malloc(sizeof(struct struct_a));
	struct struct_a* b = malloc(sizeof(struct struct_a));
	struct struct_a* c = malloc(sizeof(struct struct_a));
	struct struct_a* d = malloc(sizeof(struct struct_a));
	a->sort_param = 190;
	b->sort_param = 10;
	c->sort_param = 70;
	d->sort_param = 30;
	heap_add(heap, a);
	heap_add(heap, b);
	heap_add(heap, c);
	heap_add(heap, d);
	int data[4] = {190, 70, 30, 10};
	for (int i = 0; i < 4; ++i)
	{
		struct struct_a* item = heap_remove(heap);
		const int compared = item->sort_param == data[i];
		printf("%s \n", compared ? "TRUE" : "FALSE");
	}

	heap_destroy(&heap, TRUE);
	return 0;
}
