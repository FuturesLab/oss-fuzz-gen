#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
  cJSON *json = NULL;
  cJSON *detached_item = NULL;
  char *key = NULL;

  if (size == 0) {
    return 0;
  }

  // Ensure the data is null-terminated
  char *json_data = (char *)malloc(size + 1);
  if (json_data == NULL) {
    return 0;
  }
  memcpy(json_data, data, size);
  json_data[size] = '\0';

  // Parse the JSON data
  json = cJSON_Parse(json_data);
  free(json_data);

  if (json == NULL) {
    return 0;
  }

  // Allocate memory for the key
  key = (char *)malloc(size + 1);
  if (key == NULL) {
    cJSON_Delete(json);
    return 0;
  }

  // Copy part of the data to use as a key
  memcpy(key, data, size);
  key[size] = '\0';

  // Detach item from object case-sensitive
  detached_item = cJSON_DetachItemFromObjectCaseSensitive(json, key);

  // Clean up
  if (detached_item != NULL) {
    cJSON_Delete(detached_item);
  }
  cJSON_Delete(json);
  free(key);

  return 0;
}

#ifdef __cplusplus
}
#endif