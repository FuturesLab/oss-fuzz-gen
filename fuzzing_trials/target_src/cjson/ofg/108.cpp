#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
  void *memory_to_free;
  
  // Ensure that size is non-zero to allocate memory
  if (size == 0) {
    return 0;
  }

  // Allocate memory based on the input size
  memory_to_free = malloc(size);
  if (memory_to_free == NULL) {
    return 0;
  }

  // Copy the input data to the allocated memory
  memcpy(memory_to_free, data, size);

  // Call the function-under-test
  cJSON_free(memory_to_free);

  return 0;
}

#ifdef __cplusplus
}
#endif