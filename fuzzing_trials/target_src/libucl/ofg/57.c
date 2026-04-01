#include "ucl.h"
#include <inttypes.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
  // Ensure that we have enough data to form an int64_t
  if (size < sizeof(int64_t)) {
    return 0;
  }

  // Extract an int64_t value from the input data
  int64_t value;
  memcpy(&value, data, sizeof(int64_t));

  // Call the function-under-test
  ucl_object_t *obj = ucl_object_fromint(value);

  // Free the created object to avoid memory leaks
  ucl_object_unref(obj);

  return 0;
}