#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
  // Ensure the size is sufficient to divide into two parts
  if (size < 2) {
    return 0;
  }

  // Create two ucl_object_t objects
  ucl_object_t *array = ucl_object_new();
  ucl_object_t *element = ucl_object_new();

  // Initialize the array and element with some data
  ucl_object_insert_key(array, ucl_object_fromstring("value1"), "key1", 4, false);
  ucl_object_insert_key(element, ucl_object_fromstring("value2"), "key2", 4, false);

  // Call the function-under-test
  ucl_object_t *result = ucl_array_delete(array, element);

  // Clean up
  ucl_object_unref(array);
  ucl_object_unref(element);
  if (result != NULL) {
    ucl_object_unref(result);
  }

  return 0;
}