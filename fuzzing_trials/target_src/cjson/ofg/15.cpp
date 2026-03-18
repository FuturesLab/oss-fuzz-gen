#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  // Parse the input data into a cJSON object
  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  // Create an array reference from the parsed cJSON object
  cJSON *array_ref = cJSON_CreateArrayReference(json);
  if (array_ref != NULL) {
    // Clean up the created array reference
    cJSON_Delete(array_ref);
  }

  // Clean up the original cJSON object
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif