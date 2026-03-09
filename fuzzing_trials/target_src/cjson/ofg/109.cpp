#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
  if (size == 0) return 0;

  // Ensure the input data is null-terminated
  char *key = (char *)malloc(size + 1);
  if (key == NULL) return 0;
  memcpy(key, data, size);
  key[size] = '\0';

  // Create a new cJSON object
  cJSON *object = cJSON_CreateObject();
  if (object == NULL) {
    free(key);
    return 0;
  }

  // Call the function-under-test
  cJSON *result = cJSON_AddTrueToObject(object, key);

  // Clean up
  cJSON_Delete(object);
  free(key);

  return 0;
}

#ifdef __cplusplus
}
#endif