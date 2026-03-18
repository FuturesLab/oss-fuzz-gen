#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_192(const uint8_t *data, size_t size) {
  // Ensure size is greater than 0 to have at least one character for the key
  if (size == 0) {
    return 0;
  }

  // Create a UCL object
  ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);

  // Use the first part of the data as a key
  char key[256];
  size_t key_len = size < 255 ? size : 255;
  memcpy(key, data, key_len);
  key[key_len] = '\0'; // Ensure null-termination

  // Add a dummy key-value pair to the object
  ucl_object_insert_key(obj, ucl_object_fromstring("dummy_value"), key, key_len, false);

  // Call the function-under-test
  bool result = ucl_object_delete_key(obj, key);

  // Clean up
  ucl_object_unref(obj);

  return 0;
}