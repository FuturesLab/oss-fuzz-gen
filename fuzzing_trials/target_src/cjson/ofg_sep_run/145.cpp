#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Split the input data into two parts
  size_t half_size = size / 2;
  const char *key = (const char *)data;
  size_t key_length = half_size;
  const uint8_t *value_data = data + half_size;
  size_t value_size = size - half_size;

  // Ensure null-terminated strings
  char *key_str = (char *)malloc(key_length + 1);
  if (!key_str) {
    return 0;
  }
  memcpy(key_str, key, key_length);
  key_str[key_length] = '\0';

  // Parse the second half of the data as a cJSON object
  cJSON *value_item = cJSON_ParseWithLength((const char *)value_data, value_size);
  if (!value_item) {
    free(key_str);
    return 0;
  }

  // Create a new cJSON object
  cJSON *json_object = cJSON_CreateObject();
  if (!json_object) {
    cJSON_Delete(value_item);
    free(key_str);
    return 0;
  }

  // Call the function under test
  cJSON_bool result = cJSON_AddItemReferenceToObject(json_object, key_str, value_item);

  // Clean up
  cJSON_Delete(json_object);
  cJSON_Delete(value_item);
  free(key_str);

  return 0;
}

#ifdef __cplusplus
}
#endif