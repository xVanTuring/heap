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
#include "heap.h"
static int heapExtendArray(HEAP *heap);

HEAP *heap_create(int nalloc, int direction) {
  if (nalloc < MIN_BUFFER_SIZE)
    nalloc = MIN_BUFFER_SIZE;
  HEAP *heap;
  if ((heap = (HEAP *)calloc(1, sizeof(HEAP))) == NULL) {
    return NULL;
  }
  if ((heap->array = (void **)calloc(nalloc, sizeof(void *))) == NULL) {
    heap_destroy(&heap, 0);
    return NULL;
  }
  heap->nalloc = nalloc;
  heap->n = 0;
  heap->direction = direction;
  return heap;
}

void heap_destroy(HEAP **pheap, const int freeflag) {
  HEAP *heap;
  if (pheap == NULL) {
    return;
  }
  if ((heap = *pheap) == NULL) {
    return;
  }
  if (freeflag) {
    for (size_t i = 0; i < heap->n; i++) {
      free(heap->array[i]);
    }
  } else if (heap->n > 0) {
    //
  }
  if (heap->array)
    free(heap->array);
  free(heap);
  *pheap = NULL;
}

int heap_add(HEAP *heap, void *item) {
  if (!heap)
    return 1;
  if (!item)
    return 1;
  if (heap->n >= heap->nalloc)
    heapExtendArray(heap);
  heap->array[heap->n] = item;
  heap->n++;
  heap_swap_up(heap, heap->n - 1);
  return 0;
}

void *heap_remove(HEAP *heap) {
  if (!heap) {
    return NULL;
  }
  if (heap->n == 0) {
    return NULL;
  }
  void *item = heap->array[0];
  heap->array[0] = heap->array[heap->n - 1];
  heap->array[heap->n - 1] = NULL;
  heap->n--;
  heap_swap_down(heap);
  return item;
}

int heap_sort(HEAP *heap) {
  if (!heap) {
    return 1;
  }
  for (size_t i = 0; i < heap->n; i++) {
    heap_swap_up(heap, i);
  }
  return 0;
}

size_t heap_get_count(HEAP *heap) {
  if (!heap) {
    return 0;
  }
  return heap->n;
}

int heap_sort_strict_order(HEAP *heap) {
  size_t i;
  if (!heap) {
    return 1;
  }
  const size_t size = heap->n;
  for (i = 0; i < size; i++) {
    const size_t index = size - i;
    SWAP_ITEMS(0, index - 1);
    heap->n--;
    heap_swap_down(heap);
  }
  heap->n = size;
  for (i = 0; i < size / 2; i++) {
    SWAP_ITEMS(i, size - i - 1);
  }
  return 0;
}

int heap_swap_up(HEAP *heap, size_t index) {
  if (!heap) {
    return 1;
  }
  if (index < 0 || index >= heap->n) {
    return 1;
  }
  size_t ic = index + 1;
  size_t ip;
  size_t val_par, val_chd;
  if (heap->direction == SORT_INCREASING) {
    while (1) {
      if (ic == 1)
        break;
      ip = ic / 2;
      val_chd = *(size_t *)(heap->array[ic - 1]);
      val_par = *(size_t *)(heap->array[ip - 1]);
      if (val_par <= val_chd) {
        break;
      }
      SWAP_ITEMS(ip - 1, ic - 1);
      ic = ip;
    }
  } else {
    while (1) {
      if (ic == 1)
        break;
      ip = ic / 2;
      val_chd = *(size_t *)(heap->array[ic - 1]);
      val_par = *(size_t *)(heap->array[ip - 1]);

      if (val_par >= val_chd) {
        break;
      }

      SWAP_ITEMS(ip - 1, ic - 1);
      ic = ip;
    }
  }
  return 0;
}

int heap_swap_down(HEAP *heap) {
  if (!heap) {
    return 1;
  }
  if (heap_get_count(heap) < 1) {
    return 0;
  }
  size_t ip = 1;
  size_t icr, icl;
  size_t val_par, val_chd_lft, val_chd_rgt;
  if (heap->direction == SORT_INCREASING) {
    while (1) {
      icl = 2 * ip;
      if (icl > heap->n)
        break;
      val_par = *(size_t *)(heap->array[ip - 1]);
      val_chd_lft = *(size_t *)(heap->array[icl - 1]);
      icr = icl + 1;
      if (icr > heap->n) {
        /* only a left child; no iters below */
        if (val_par > val_chd_lft)
          SWAP_ITEMS(ip - 1, icl - 1);
        break;
      } else {
        /* both children exist; swap with the smallest if bigger */
        val_chd_rgt = *(size_t *)(heap->array[icr - 1]);
        if (val_par <= val_chd_lft &&
            val_par <= val_chd_rgt) /* smaller than both */
          break;
        if (val_chd_lft <= val_chd_rgt) {
          /* left smaller; swap */
          SWAP_ITEMS(ip - 1, icl - 1);
          ip = icl;
        } else {
          /* right smaller; swap */
          SWAP_ITEMS(ip - 1, icr - 1);
          ip = icr;
        }
      }
    }
  } else {
    while (1) {
      icl = 2 * ip;
      if (icl > heap->n)
        break;
      val_par = *(size_t *)(heap->array[ip - 1]);
      val_chd_lft = *(size_t *)(heap->array[icl - 1]);
      icr = icl + 1;
      if (icr > heap->n) {
        /* only a left child; no iters below */
        if (val_par < val_chd_lft)
          SWAP_ITEMS(ip - 1, icl - 1);
        break;
      } else {
        /* both children exist; swap with the biggest if smaller */
        val_chd_rgt = *(size_t *)(heap->array[icr - 1]);
        if (val_par >= val_chd_lft &&
            val_par >= val_chd_rgt) /* bigger than both */
          break;
        if (val_chd_lft >= val_chd_rgt) {
          /* left bigger; swap */
          SWAP_ITEMS(ip - 1, icl - 1);
          ip = icl;
        } else {
          /* right bigger; swap */
          SWAP_ITEMS(ip - 1, icr - 1);
          ip = icr;
        }
      }
    }
  }
  return 0;
}

static int heapExtendArray(HEAP *heap) {
  if (!heap)
    return 1;
  heap->array =
      (void **)re_alloc((void **)&heap->array, sizeof(void *) * heap->nalloc,
                        2 * sizeof(void *) * heap->nalloc);
  if (heap->array == NULL) {
    return 1;
  }
  heap->nalloc = 2 * heap->nalloc;
  return 0;
}
