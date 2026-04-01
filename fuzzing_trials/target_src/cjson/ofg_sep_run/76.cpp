#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Create a JSON object to add the boolean to
  cJSON *json_object = cJSON_CreateObject();
  if (json_object == NULL) {
    return 0;
  }

  // Extract a boolean value from the data
  cJSON_bool bool_value = (data[0] % 2 == 0) ? cJSON_True : cJSON_False;

  // Ensure the string is null-terminated for the key
  size_t key_length = size - 1;
  char *key = (char *)malloc(key_length + 1);
  if (key == NULL) {
    cJSON_Delete(json_object);
    return 0;
  }
  memcpy(key, data + 1, key_length);
  key[key_length] = '\0';

  // Call the function-under-test
  cJSON *result = cJSON_AddBoolToObject(json_object, key, bool_value);

  // Clean up
  free(key);
  cJSON_Delete(json_object);

  return 0;
}

#ifdef __cplusplus
}
#endif