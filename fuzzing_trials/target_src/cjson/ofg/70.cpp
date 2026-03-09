#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
  if (size == 0) return 0;

  // Ensure the data is null-terminated for string operations
  char *key = (char *)malloc(size + 1);
  if (key == NULL) return 0;
  memcpy(key, data, size);
  key[size] = '\0';

  // Create a cJSON object
  cJSON *json = cJSON_CreateObject();
  if (json == NULL) {
    free(key);
    return 0;
  }

  // Call the function under test
  cJSON *result = cJSON_AddNullToObject(json, key);

  // Clean up
  cJSON_Delete(json);
  free(key);

  return 0;
}

#ifdef __cplusplus
}
#endif