#include "ucl.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Initialize a ucl_object_t and a _Bool variable
  ucl_object_t *obj = ucl_object_fromstring((const char *)data);
  _Bool result = false;

  // Call the function-under-test
  ucl_object_toboolean_safe(obj, &result);

  // Cleanup
  ucl_object_unref(obj);

  return 0;
}