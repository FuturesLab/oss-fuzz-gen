#include "ucl.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Initialize a ucl_object_t and a _Bool variable
  ucl_object_t *ucl_obj = ucl_object_fromstring((const char *)data);
  _Bool result_bool = false;

  // Call the function-under-test
  bool success = ucl_object_toboolean_safe(ucl_obj, &result_bool);

  // Clean up
  ucl_object_unref(ucl_obj);

  return 0;
}