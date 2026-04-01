#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
  // Ensure the data is null-terminated and not empty
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  // Create a cJSON string using the input data
  cJSON *json_string = cJSON_CreateString((const char *)data);

  // Clean up the cJSON object
  if (json_string != NULL) {
    cJSON_Delete(json_string);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif