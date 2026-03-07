#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
  // Ensure that the data is not NULL and size is greater than 0
  if (data == NULL || size == 0) {
    return 0;
  }

  // Call the function-under-test
  ucl_object_t *obj = ucl_object_fromlstring((const char *)data, size);

  // Clean up the object if it was created successfully
  if (obj != NULL) {
    ucl_object_unref(obj);
  }

  return 0;
}