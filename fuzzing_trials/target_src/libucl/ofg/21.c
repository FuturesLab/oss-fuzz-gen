#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
  // Initialize two ucl_object_t pointers
  ucl_object_t *array_obj = ucl_object_typed_new(UCL_ARRAY);
  ucl_object_t *element_obj = ucl_object_fromstring_common((const char *)data, size, 0);

  // Ensure that element_obj is not NULL before proceeding
  if (element_obj == NULL) {
    ucl_object_unref(array_obj);
    return 0;
  }

  // Call the function under test
  bool result = ucl_array_append(array_obj, element_obj);

  // Clean up
  ucl_object_unref(array_obj);
  ucl_object_unref(element_obj);

  return 0;
}