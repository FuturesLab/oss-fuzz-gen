#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Create two cJSON objects
  cJSON *object = cJSON_CreateObject();
  cJSON *item = cJSON_CreateObject();

  if (object == NULL || item == NULL) {
    cJSON_Delete(object);
    cJSON_Delete(item);
    return 0;
  }

  // Use the data to create a string key
  char *key = (char *)malloc(size + 1);
  if (key == NULL) {
    cJSON_Delete(object);
    cJSON_Delete(item);
    return 0;
  }

  memcpy(key, data, size);
  key[size] = '\0';

  // Call the function under test
  cJSON_bool result = cJSON_AddItemReferenceToObject(object, key, item);

  // Clean up
  free(key);
  cJSON_Delete(object);
  cJSON_Delete(item);

  return 0;
}

#ifdef __cplusplus
}
#endif