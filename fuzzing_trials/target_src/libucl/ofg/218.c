#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

// Define UCL_TYPE_MAX based on the known values of ucl_type_t
#ifndef UCL_TYPE_MAX
#define UCL_TYPE_MAX 6 // Assuming there are 6 types, adjust this number based on the actual ucl_type_t enum
#endif

int LLVMFuzzerTestOneInput_218(const uint8_t *data, size_t size) {
  // Ensure there is at least one byte to read
  if (size < 1) {
    return 0;
  }

  // Use the first byte of data to determine the ucl_type_t
  ucl_type_t type = (ucl_type_t)(data[0] % UCL_TYPE_MAX);

  // Call the function-under-test
  ucl_object_t *obj = ucl_object_typed_new(type);

  // Clean up the created object
  if (obj != NULL) {
    ucl_object_unref(obj);
  }

  return 0;
}