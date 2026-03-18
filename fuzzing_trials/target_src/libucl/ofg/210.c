#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_210(const uint8_t *data, size_t size) {
  // Ensure the input data is null-terminated
  if (size == 0) {
    return 0;
  }

  // Allocate memory for a null-terminated string
  char *null_terminated_data = (char *)malloc(size + 1);
  if (null_terminated_data == NULL) {
    return 0;
  }

  // Copy the input data and null-terminate it
  memcpy(null_terminated_data, data, size);
  null_terminated_data[size] = '\0';

  // Call the function-under-test
  ucl_object_t *obj = ucl_object_fromstring(null_terminated_data);

  // Clean up
  if (obj != NULL) {
    ucl_object_unref(obj);
  }
  free(null_terminated_data);

  return 0;
}