#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include string.h for memcpy

int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
  // Ensure we have enough data to extract a double
  if (size < sizeof(double)) {
    return 0;
  }

  // Extract a double from the input data
  double value;
  memcpy(&value, data, sizeof(double));

  // Call the function-under-test
  ucl_object_t *obj = ucl_object_fromdouble(value);

  // Clean up
  if (obj != NULL) {
    ucl_object_unref(obj);
  }

  return 0;
}