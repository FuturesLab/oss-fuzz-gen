#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
  // Ensure size is sufficient for creating a valid key
  if (size < 1) {
    return 0;
  }

  // Create a ucl_object_t object
  ucl_object_t *obj = ucl_object_new();

  // Use the data as a key, ensuring it is null-terminated
  char key[size + 1];
  memcpy(key, data, size);
  key[size] = '\0';

  // Add a dummy key-value pair to the object
  ucl_object_insert_key(obj, ucl_object_fromstring("value"), "dummy_key", 0, false);

  // Call the function-under-test
  ucl_object_t *popped_obj = ucl_object_pop_key(obj, key);

  // Clean up
  if (popped_obj != NULL) {
    ucl_object_unref(popped_obj);
  }
  ucl_object_unref(obj);

  return 0;
}