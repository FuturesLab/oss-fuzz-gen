#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
  if (size < 3) return 0;

  // Split the data into two parts for key and value strings
  size_t key_len = data[0] % (size - 2) + 1; // Ensure at least 1 byte for key
  size_t value_len = size - key_len - 1;

  // Allocate memory for key and value strings
  char *key = (char *)malloc(key_len + 1);
  char *value = (char *)malloc(value_len + 1);

  if (key == NULL || value == NULL) {
    free(key);
    free(value);
    return 0;
  }

  // Copy the data into key and value, ensuring null termination
  memcpy(key, data + 1, key_len);
  key[key_len] = '\0';

  memcpy(value, data + 1 + key_len, value_len);
  value[value_len] = '\0';

  // Create a cJSON object
  cJSON *json = cJSON_CreateObject();
  if (json == NULL) {
    free(key);
    free(value);
    return 0;
  }

  // Call the function-under-test
  cJSON *result = cJSON_AddStringToObject(json, key, value);

  // Clean up
  cJSON_Delete(json);
  free(key);
  free(value);

  return 0;
}

#ifdef __cplusplus
}
#endif