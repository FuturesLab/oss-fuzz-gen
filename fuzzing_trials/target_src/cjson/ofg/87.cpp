#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
  if (size < 2) return 0; // Ensure there's enough data for a key

  // Split the input data into two parts: JSON string and key
  size_t json_str_size = size / 2;
  size_t key_size = size - json_str_size;

  // Ensure the JSON string and key are null-terminated
  char *json_str = (char *)malloc(json_str_size + 1);
  char *key = (char *)malloc(key_size + 1);

  if (json_str == NULL || key == NULL) {
    free(json_str);
    free(key);
    return 0;
  }

  memcpy(json_str, data, json_str_size);
  json_str[json_str_size] = '\0';

  memcpy(key, data + json_str_size, key_size);
  key[key_size] = '\0';

  // Parse the JSON string
  cJSON *json = cJSON_Parse(json_str);
  if (json != NULL) {
    // Call the function-under-test
    cJSON *item = cJSON_GetObjectItemCaseSensitive(json, key);

    // Clean up
    cJSON_Delete(json);
  }

  free(json_str);
  free(key);

  return 0;
}

#ifdef __cplusplus
}
#endif