#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
  cJSON *json_object = cJSON_CreateObject();
  if (json_object == NULL) {
    return 0;
  }

  // Ensure the string is null-terminated
  char *key = (char *)malloc(size + 1);
  if (key == NULL) {
    cJSON_Delete(json_object);
    return 0;
  }
  memcpy(key, data, size);
  key[size] = '\0';

  // Call the function-under-test
  cJSON *result = cJSON_AddNullToObject(json_object, key);

  // Clean up
  free(key);
  cJSON_Delete(json_object);

  return 0;
}

#ifdef __cplusplus
}
#endif