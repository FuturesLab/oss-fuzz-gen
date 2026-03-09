#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_180(const uint8_t *data, size_t size) {
  // Create two ucl_object_t objects to use as parameters
  ucl_object_t *obj1 = ucl_object_new();
  ucl_object_t *obj2 = ucl_object_new();

  // Ensure the objects are not NULL
  if (obj1 == NULL || obj2 == NULL) {
    return 0;
  }

  // Add some data to the objects to avoid them being empty
  ucl_object_insert_key(obj1, ucl_object_fromstring("value1"), "key1", 4, false);
  ucl_object_insert_key(obj2, ucl_object_fromstring("value2"), "key2", 4, false);

  // Call the function-under-test
  ucl_object_t *result = ucl_elt_append(obj1, obj2);

  // Clean up
  ucl_object_unref(result);
  ucl_object_unref(obj1);
  ucl_object_unref(obj2);

  return 0;
}