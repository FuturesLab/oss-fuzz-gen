#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
  // Ensure size is sufficient to create a non-empty string
  if (size < 1) {
    return 0;
  }

  // Create and initialize ucl_object_t objects
  ucl_object_t *obj1 = ucl_object_new();
  ucl_object_t *obj2 = ucl_object_new();

  // Create a null-terminated string from data
  char *comment = (char *)malloc(size + 1);
  if (comment == NULL) {
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);
    return 0;
  }
  memcpy(comment, data, size);
  comment[size] = '\0';

  // Call the function under test
  ucl_comments_add(obj1, obj2, comment);

  // Clean up
  free(comment);
  ucl_object_unref(obj1);
  ucl_object_unref(obj2);

  return 0;
}