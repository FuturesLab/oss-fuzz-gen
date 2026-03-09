#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Split the input data into two parts for key and raw value
  size_t key_length = data[0] % (size - 1) + 1;  // Ensure key length is at least 1
  size_t raw_length = size - key_length;

  char *key = (char *)malloc(key_length + 1);
  char *raw = (char *)malloc(raw_length + 1);

  if (key == NULL || raw == NULL) {
    free(key);
    free(raw);
    return 0;
  }

  memcpy(key, data + 1, key_length);
  key[key_length] = '\0';

  memcpy(raw, data + 1 + key_length, raw_length);
  raw[raw_length] = '\0';

  cJSON *json_object = cJSON_CreateObject();
  if (json_object == NULL) {
    free(key);
    free(raw);
    return 0;
  }

  cJSON *result = cJSON_AddRawToObject(json_object, key, raw);

  // Clean up
  cJSON_Delete(json_object);
  free(key);
  free(raw);

  return 0;
}

#ifdef __cplusplus
}
#endif