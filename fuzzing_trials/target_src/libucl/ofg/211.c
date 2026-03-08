#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_211(const uint8_t *data, size_t size) {
  // Check if size is 0 to prevent unnecessary operations
  if (size == 0) {
    return 0;
  }

  // Create a new UCL object
  ucl_object_t *obj = ucl_object_new();

  // Choose a size for reservation, using the size of the input data
  size_t reserve_size = size % 100; // Limit the reserve size to a reasonable number

  // Call the function-under-test
  bool result = ucl_object_reserve(obj, reserve_size);

  // Clean up the UCL object
  ucl_object_unref(obj);

  return 0;
}