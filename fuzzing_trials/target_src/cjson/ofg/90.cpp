#include <stdint.h>
#include <stdlib.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
  // Check if the data is null or size is zero
  if (data == NULL || size == 0) {
    return 0;
  }

  // Create a cJSON object from the input data
  cJSON *json = cJSON_ParseWithLength((const char *)data, size);

  // Clean up the cJSON object to avoid memory leaks
  if (json != NULL) {
    cJSON_Delete(json);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif