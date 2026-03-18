#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

// Function for fuzzing
int LLVMFuzzerTestOneInput_214(const uint8_t *data, size_t size) {
  // Initialize a ucl_object_t object
  ucl_object_t *obj = ucl_object_new();

  // Ensure the size parameter is non-zero for meaningful testing
  size_t reserve_size = size > 0 ? size : 1;

  // Call the function-under-test
  bool result = ucl_object_reserve(obj, reserve_size);

  // Clean up
  ucl_object_unref(obj);

  return 0;
}