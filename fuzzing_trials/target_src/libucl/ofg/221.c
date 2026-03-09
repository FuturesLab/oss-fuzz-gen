#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_221(const uint8_t *data, size_t size) {
  // Initialize a ucl_object_t from the input data
  ucl_object_t *obj = ucl_object_fromstring_common((const char *)data, size, 0);
  
  // Initialize a double variable to store the result
  double result = 0.0;

  // Call the function-under-test
  bool success = ucl_object_todouble_safe(obj, &result);

  // Clean up
  if (obj != NULL) {
    ucl_object_unref(obj);
  }

  return 0;
}