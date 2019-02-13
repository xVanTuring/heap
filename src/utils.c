#include "utils.h"

void *re_alloc(void **p_in_data, size_t oldSize, size_t newSize) {
  void *new_data;
  if (!p_in_data) {
    return NULL;
  }
  void *in_data = *p_in_data;
  if (newSize <= 0) {
    if (in_data) {
      free(in_data);
      *p_in_data = NULL;
    }
    return NULL;
  }
  if (!in_data) {
    new_data = (void *)calloc(1, newSize);
    if (new_data == NULL) {
      return NULL;
    }
    return new_data;
  }
  new_data = (void *)calloc(1, newSize);
  if (new_data == NULL) {
    return NULL;
  }
  const size_t min_size = MIN(oldSize, newSize);
  memcpy(new_data, in_data, min_size);
  free(in_data);
  *p_in_data = NULL;
  return new_data;
}
