#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
  if (size < 2) return 0; // Ensure there's enough data for at least a key and a value

  // Split the data into a key and a value
  size_t key_length = data[0] % (size - 1) + 1; // Ensure key length is at least 1
  if (key_length >= size) return 0; // Check if key length is valid
  char *key = (char *)malloc(key_length + 1);
  if (key == NULL) return 0;
  memcpy(key, data + 1, key_length);
  key[key_length] = '\0'; // Null-terminate the key

  // Create a cJSON object
  cJSON *json = cJSON_CreateObject();
  if (json == NULL) {
    free(key);
    return 0;
  }

  // Convert remaining data to a double value
  const double value = (double)data[key_length + 1];

  // Call the function-under-test
  cJSON *result = cJSON_AddNumberToObject(json, key, value);

  // Clean up
  free(key);
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif