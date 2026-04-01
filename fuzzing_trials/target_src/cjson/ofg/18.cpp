#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
  cJSON *root = cJSON_CreateObject();
  cJSON *new_object = NULL;
  char *key = NULL;

  // Ensure the data is null-terminated and non-empty for key
  if (size == 0 || data[size - 1] != '\0') {
    cJSON_Delete(root);
    return 0;
  }

  // Create a key from the input data
  key = (char *)malloc(size);
  if (key == NULL) {
    cJSON_Delete(root);
    return 0;
  }
  memcpy(key, data, size);
  key[size - 1] = '\0'; // Ensure null-termination

  // Call the function-under-test
  new_object = cJSON_AddObjectToObject(root, key);

  // Clean up
  free(key);
  cJSON_Delete(root);

  return 0;
}

#ifdef __cplusplus
}
#endif