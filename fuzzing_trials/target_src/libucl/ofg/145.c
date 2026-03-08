#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
  // Ensure the input data is not empty
  if (size == 0) {
    return 0;
  }

  // Allocate memory for the string and ensure it's null-terminated
  char *input_string = (char *)malloc(size + 1);
  if (input_string == NULL) {
    return 0;
  }
  memcpy(input_string, data, size);
  input_string[size] = '\0';

  // Declare a variable for ucl_type_t
  ucl_type_t type;

  // Call the function under test
  ucl_object_string_to_type(input_string, &type);

  // Free the allocated memory
  free(input_string);

  return 0;
}