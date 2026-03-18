#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Split the input data into two parts for key and JSON data
  size_t key_length = data[0] % (size - 1) + 1; // Ensure key_length is at least 1 and less than size
  size_t json_data_length = size - key_length; 

  char *key = (char *)malloc(key_length + 1);
  char *json_data = (char *)malloc(json_data_length + 1);

  if (!key || !json_data) {
    free(key);
    free(json_data);
    return 0;
  }

  memcpy(key, data + 1, key_length);
  key[key_length] = '\0';

  memcpy(json_data, data + 1 + key_length, json_data_length);
  json_data[json_data_length] = '\0';

  cJSON *object = cJSON_Parse(json_data);
  cJSON *new_item = cJSON_CreateString("replacement");

  if (object && new_item) {
    cJSON_ReplaceItemInObjectCaseSensitive(object, key, new_item);
  }

  cJSON_Delete(object);
  cJSON_Delete(new_item);
  free(key);
  free(json_data);

  return 0;
}

#ifdef __cplusplus
}
#endif