#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
  // Ensure there's at least one byte to read for the size
  if (size < sizeof(size_t)) {
    return 0;
  }

  // Use the first few bytes of data to determine the size for cJSON_malloc
  size_t malloc_size = *(const size_t *)data;

  // Call cJSON_malloc with the derived size
  void *allocated_memory = cJSON_malloc(malloc_size);

  // Free the allocated memory if it's not NULL
  if (allocated_memory != NULL) {
    free(allocated_memory);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif