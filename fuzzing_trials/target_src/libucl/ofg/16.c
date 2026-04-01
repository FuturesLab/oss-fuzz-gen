#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
  // Ensure that we have enough data to extract a ucl_type_t value
  if (size < sizeof(ucl_type_t)) {
    return 0;
  }

  // Extract a ucl_type_t value from the input data
  ucl_type_t type = *(const ucl_type_t *)data;

  // Call the function-under-test
  const char *result = ucl_object_type_to_string(type);

  // Use the result in some way to prevent compiler optimizations from removing the call
  if (result != NULL) {
    // For example, we can check the length of the result string
    size_t len = 0;
    while (result[len] != '\0') {
      len++;
    }
  }

  return 0;
}