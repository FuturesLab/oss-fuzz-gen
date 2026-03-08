#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
  if (size < 3) return 0; // Ensure there's enough data for meaningful processing

  // Split the input data into three parts
  size_t json1_size = size / 3;
  size_t key_size = size / 3;
  size_t json2_size = size - json1_size - key_size;

  // Ensure null-terminated strings for cJSON parsing
  char *json1_str = (char *)malloc(json1_size + 1);
  char *key_str = (char *)malloc(key_size + 1);
  char *json2_str = (char *)malloc(json2_size + 1);

  if (!json1_str || !key_str || !json2_str) {
    free(json1_str);
    free(key_str);
    free(json2_str);
    return 0;
  }

  memcpy(json1_str, data, json1_size);
  json1_str[json1_size] = '\0';

  memcpy(key_str, data + json1_size, key_size);
  key_str[key_size] = '\0';

  memcpy(json2_str, data + json1_size + key_size, json2_size);
  json2_str[json2_size] = '\0';

  // Parse the JSON strings
  cJSON *json1 = cJSON_Parse(json1_str);
  cJSON *json2 = cJSON_Parse(json2_str);

  if (json1 && json2) {
    // Call the function-under-test
    cJSON_ReplaceItemInObject(json1, key_str, json2);
  }

  // Clean up
  cJSON_Delete(json1);
  cJSON_Delete(json2);
  free(json1_str);
  free(key_str);
  free(json2_str);

  return 0;
}

#ifdef __cplusplus
}
#endif