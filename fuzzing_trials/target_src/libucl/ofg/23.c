#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h> // Include this for the bool type

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
  // Create two ucl_object_t instances
  ucl_object_t *array = ucl_object_typed_new(UCL_ARRAY);
  ucl_object_t *element = ucl_object_fromstring((const char *)data);

  // Call the function-under-test
  bool result = ucl_array_append(array, element);

  // Clean up the created objects
  ucl_object_unref(array);
  ucl_object_unref(element);

  return 0;
}