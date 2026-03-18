#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
  if (size < 2) return 0; // Ensure there's enough data for meaningful operations

  // Parse the input data as a JSON object
  cJSON *json = cJSON_ParseWithLength((const char *)data, size);
  if (json == NULL) return 0;

  // Create a new item to replace with
  cJSON *new_item = cJSON_CreateString("replacement_value");
  if (new_item == NULL) {
    cJSON_Delete(json);
    return 0;
  }

  // Use a portion of the data as a key
  size_t key_length = (size > 10) ? 10 : size - 1;
  char *key = (char *)malloc(key_length + 1);
  if (key == NULL) {
    cJSON_Delete(json);
    cJSON_Delete(new_item);
    return 0;
  }
  memcpy(key, data, key_length);
  key[key_length] = '\0';

  // Call the function under test
  cJSON_ReplaceItemInObjectCaseSensitive(json, key, new_item);

  // Clean up
  free(key);
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif