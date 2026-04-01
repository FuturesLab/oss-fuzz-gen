#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Ensure that data is null-terminated for string operations
  char *key = (char *)malloc(size + 1);
  if (key == NULL) {
    return 0;
  }
  memcpy(key, data, size);
  key[size] = '\0';

  // Create a simple JSON object with a few key-value pairs
  cJSON *json = cJSON_CreateObject();
  if (json == NULL) {
    free(key);
    return 0;
  }
  cJSON_AddStringToObject(json, "key1", "value1");
  cJSON_AddStringToObject(json, "key2", "value2");
  cJSON_AddStringToObject(json, "key3", "value3");

  // Call the function-under-test
  cJSON_DeleteItemFromObjectCaseSensitive(json, key);

  // Clean up
  cJSON_Delete(json);
  free(key);

  return 0;
}

#ifdef __cplusplus
}
#endif