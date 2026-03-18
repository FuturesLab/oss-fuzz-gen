#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
  if (size < 2) return 0; // Ensure there's enough data for a key and JSON

  // Allocate memory for the key and JSON string
  size_t key_size = data[0] % (size - 1) + 1; // Ensure key size is less than size
  char *key = (char *)malloc(key_size + 1);
  if (!key) return 0;

  // Copy the key from the data
  memcpy(key, data + 1, key_size);
  key[key_size] = '\0'; // Null-terminate the key

  // Parse the remaining data as JSON
  cJSON *json = cJSON_Parse((const char *)(data + 1 + key_size));
  if (!json) {
    free(key);
    return 0;
  }

  // Call the function-under-test
  cJSON *item = cJSON_GetObjectItem(json, key);

  // Clean up
  cJSON_Delete(json);
  free(key);

  return 0;
}

#ifdef __cplusplus
}
#endif