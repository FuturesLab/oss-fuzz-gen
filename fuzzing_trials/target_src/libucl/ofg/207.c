#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_207(const uint8_t *data, size_t size) {
  // Ensure the input data is null-terminated for the function to process it as a string
  if (size == 0) {
    return 0;
  }

  // Allocate a buffer with an extra byte for the null terminator
  char *input = (char *)malloc(size + 1);
  if (input == NULL) {
    return 0;
  }

  // Copy the data into the buffer and null-terminate it
  memcpy(input, data, size);
  input[size] = '\0';

  // Call the function under test
  ucl_object_t *obj = ucl_object_fromstring(input);

  // Free the allocated object if it's not NULL
  if (obj != NULL) {
    ucl_object_unref(obj);
  }

  // Free the input buffer
  free(input);

  return 0;
}