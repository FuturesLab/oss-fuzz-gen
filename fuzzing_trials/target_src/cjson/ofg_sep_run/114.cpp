#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
  if (size < sizeof(int) || size % sizeof(int) != 0) {
    return 0;
  }

  int array_size = size / sizeof(int);
  int *int_array = (int *)malloc(size);
  if (int_array == NULL) {
    return 0;
  }

  memcpy(int_array, data, size);

  cJSON *json_array = cJSON_CreateIntArray(int_array, array_size);
  if (json_array != NULL) {
    cJSON_Delete(json_array);
  }

  free(int_array);

  return 0;
}

#ifdef __cplusplus
}
#endif