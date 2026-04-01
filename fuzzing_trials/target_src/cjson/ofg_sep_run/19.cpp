#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
  cJSON_Hooks hooks;
  void *(*malloc_fn)(size_t) = malloc;
  void (*free_fn)(void *) = free;

  if (size < 2) return 0;

  // Use the first byte to decide whether to use custom malloc/free functions
  if (data[0] % 2 == 0) {
    malloc_fn = NULL;
    free_fn = NULL;
  }

  hooks.malloc_fn = malloc_fn;
  hooks.free_fn = free_fn;

  cJSON_InitHooks(&hooks);

  return 0;
}

#ifdef __cplusplus
}
#endif