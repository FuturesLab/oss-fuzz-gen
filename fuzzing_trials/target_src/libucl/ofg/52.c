#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
  // Ensure the size is sufficient for a key
  if (size < 1) {
    return 0;
  }

  // Create a ucl_object_t
  ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);

  // Create a key from the data
  char *key = (char *)malloc(size + 1);
  if (key == NULL) {
    ucl_object_unref(obj);
    return 0;
  }
  memcpy(key, data, size);
  key[size] = '\0'; // Null-terminate the key

  // Add a dummy key-value pair to the object
  ucl_object_insert_key(obj, ucl_object_fromstring("dummy_value"), "dummy_key", 10, false);

  // Call the function under test
  ucl_object_delete_keyl(obj, key, size);

  // Clean up
  free(key);
  ucl_object_unref(obj);

  return 0;
}