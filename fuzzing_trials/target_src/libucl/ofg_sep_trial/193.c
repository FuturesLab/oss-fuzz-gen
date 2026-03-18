#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_193(const uint8_t *data, size_t size) {
  // Call the function-under-test
  ucl_object_t *obj = ucl_object_new();

  // Use the object in some way to ensure it is not optimized away
  // For example, we can check if the object is not NULL
  if (obj != NULL) {
    // Do something with the object, e.g., serialize it
    ucl_object_t *copy = ucl_object_copy(obj);
    if (copy != NULL) {
      ucl_object_unref(copy);
    }

    // Free the object
    ucl_object_unref(obj);
  }

  return 0;
}