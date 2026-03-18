#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Create a root JSON object
  cJSON *root = cJSON_CreateObject();
  if (root == NULL) {
    return 0;
  }

  // Create a new JSON item
  cJSON *item = cJSON_CreateString((const char *)data);
  if (item == NULL) {
    cJSON_Delete(root);
    return 0;
  }

  // Use the first byte of data to determine the length of the key
  size_t key_length = data[0] % size;
  if (key_length == 0) {
    key_length = 1; // Ensure key length is at least 1
  }

  // Ensure the key is null-terminated
  char *key = (char *)malloc(key_length + 1);
  if (key == NULL) {
    cJSON_Delete(root);
    cJSON_Delete(item);
    return 0;
  }
  memcpy(key, data + 1, key_length);
  key[key_length] = '\0';

  // Call the function-under-test
  cJSON_bool result = cJSON_AddItemToObject(root, key, item);

  // Clean up
  free(key);
  cJSON_Delete(root);

  return 0;
}

#ifdef __cplusplus
}
#endif