#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
  if (size == 0) return 0;

  // Create a cJSON object
  cJSON *json = cJSON_CreateObject();
  if (json == NULL) return 0;

  // Ensure null-terminated string for key
  char *key = (char *)malloc(size + 1);
  if (key == NULL) {
    cJSON_Delete(json);
    return 0;
  }
  memcpy(key, data, size);
  key[size] = '\0';

  // Call the function-under-test
  cJSON *result = cJSON_AddFalseToObject(json, key);

  // Clean up
  free(key);
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif