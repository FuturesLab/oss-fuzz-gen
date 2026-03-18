#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Ensure the input data is null-terminated
  char *json_data = (char *)malloc(size + 1);
  if (json_data == NULL) {
    return 0;
  }
  memcpy(json_data, data, size);
  json_data[size] = '\0';

  // Parse the input data as a cJSON object
  cJSON *json = cJSON_Parse(json_data);
  free(json_data);

  if (json == NULL) {
    return 0;
  }

  // Check if the parsed JSON is an array
  if (!cJSON_IsArray(json)) {
    cJSON_Delete(json);
    return 0;
  }

  // Detach an item from the array at a specific index
  int index = 0; // You can fuzz different indices if needed
  cJSON *detached_item = cJSON_DetachItemFromArray(json, index);

  // Clean up
  if (detached_item != NULL) {
    cJSON_Delete(detached_item);
  }
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif