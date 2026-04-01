#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
  // Allocate memory for ucl_object_t
  ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
  
  // Ensure the object is not NULL
  if (obj == NULL) {
    return 0;
  }

  // Initialize the object with some data
  // Using the input data to set a property of ucl_object_t
  obj->type = UCL_BOOLEAN;
  obj->value.iv = (size > 0) ? data[0] % 2 : 0; // Use the first byte to set a boolean value

  // Call the function under test
  bool result = ucl_object_toboolean(obj);

  // Free the allocated memory
  free(obj);

  return 0;
}