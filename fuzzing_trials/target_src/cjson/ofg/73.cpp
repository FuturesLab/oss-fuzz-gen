#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
  if (size < sizeof(size_t)) {
    return 0; // Not enough data to extract a size_t value
  }

  // Extract a size_t value from the input data
  size_t alloc_size = *((const size_t *)data);

  // Call the function-under-test
  void *allocated_memory = cJSON_malloc(alloc_size);

  // If memory was successfully allocated, free it
  if (allocated_memory != NULL) {
    free(allocated_memory);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif