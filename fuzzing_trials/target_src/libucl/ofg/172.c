#include "/src/libucl/include/ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>  // Include for the bool type

int LLVMFuzzerTestOneInput_172(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Initialize ucl_object_t pointers
  ucl_object_t *array_obj = ucl_object_typed_new(UCL_ARRAY);
  ucl_object_t *element_obj = ucl_object_fromlstring((const char *)data, size);  // Correct function name

  // Call the function-under-test
  bool result = ucl_array_prepend(array_obj, element_obj);

  // Clean up
  ucl_object_unref(array_obj);
  ucl_object_unref(element_obj);

  return 0;
}