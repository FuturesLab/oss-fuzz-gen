#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
  if (size < 3) return 0; // Ensure there is enough data for key and value

  // Create a root object
  cJSON *root = cJSON_CreateObject();
  if (root == NULL) return 0;

  // Split the data into key and value
  size_t key_len = data[0] % (size - 2) + 1; // Ensure key_len is at least 1
  size_t value_len = size - key_len - 1;
  const char *key = (const char *)(data + 1);
  const char *value = (const char *)(data + 1 + key_len);

  // Ensure null-termination for key and value
  char *key_copy = (char *)malloc(key_len + 1);
  char *value_copy = (char *)malloc(value_len + 1);
  if (key_copy == NULL || value_copy == NULL) {
    cJSON_Delete(root);
    free(key_copy);
    free(value_copy);
    return 0;
  }
  memcpy(key_copy, key, key_len);
  key_copy[key_len] = '\0';
  memcpy(value_copy, value, value_len);
  value_copy[value_len] = '\0';

  // Call the function-under-test
  cJSON *result = cJSON_AddStringToObject(root, key_copy, value_copy);

  // Clean up
  cJSON_Delete(root);
  free(key_copy);
  free(value_copy);

  return 0;
}

#ifdef __cplusplus
}
#endif