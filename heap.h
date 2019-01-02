/*====================================================================*
 -  Copyright (C) 2001 Leptonica.  All rights reserved.
 -
 -  Redistribution and use in source and binary forms, with or without
 -  modification, are permitted provided that the following conditions
 -  are met:
 -  1. Redistributions of source code must retain the above copyright
 -     notice, this list of conditions and the following disclaimer.
 -  2. Redistributions in binary form must reproduce the above
 -     copyright notice, this list of conditions and the following
 -     disclaimer in the documentation and/or other materials
 -     provided with the distribution.
 -
 -  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 -  ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 -  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 -  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL ANY
 -  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 -  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 -  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 -  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 -  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 -  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 -  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *====================================================================*/
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
