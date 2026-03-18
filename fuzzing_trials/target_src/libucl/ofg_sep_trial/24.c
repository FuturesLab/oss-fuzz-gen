#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
  // Ensure we have enough data to proceed
  if (size < 2) {
    return 0;
  }

  // Initialize two ucl_object_t objects
  ucl_object_t *array_obj = ucl_object_typed_new(UCL_ARRAY);
  ucl_object_t *element_obj = ucl_object_fromstring((const char *)data);

  // Call the function-under-test
  bool result = ucl_array_append(array_obj, element_obj);

  // Clean up
  ucl_object_unref(array_obj);
  ucl_object_unref(element_obj);

  return 0;
}