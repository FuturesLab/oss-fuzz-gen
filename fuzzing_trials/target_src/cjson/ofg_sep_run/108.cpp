#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Allocate memory and copy input data to it
  void *memory = malloc(size);
  if (memory == NULL) {
    return 0;
  }
  memcpy(memory, data, size);

  // Call the function-under-test
  cJSON_free(memory);

  return 0;
}

#ifdef __cplusplus
}
#endif