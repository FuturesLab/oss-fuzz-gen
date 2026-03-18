#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
  // Ensure that size is not zero to avoid undefined behavior
  if (size == 0) {
    return 0;
  }

  // Use the first byte of data to determine the boolean value
  bool bool_value = (data[0] % 2 == 0);

  // Call the function-under-test
  ucl_object_t *obj = ucl_object_frombool(bool_value);

  // Clean up the created object
  if (obj != NULL) {
    ucl_object_unref(obj);
  }

  return 0;
}