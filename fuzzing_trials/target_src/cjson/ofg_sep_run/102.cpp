#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Create a root JSON object
  cJSON *root = cJSON_CreateObject();
  if (root == NULL) {
    return 0;
  }

  // Create a new item to add
  cJSON *new_item = cJSON_CreateNumber(data[0]);
  if (new_item == NULL) {
    cJSON_Delete(root);
    return 0;
  }

  // Use a portion of the input data as the key
  size_t key_length = size - 1;
  char *key = (char *)malloc(key_length + 1);
  if (key == NULL) {
    cJSON_Delete(root);
    cJSON_Delete(new_item);
    return 0;
  }
  memcpy(key, data + 1, key_length);
  key[key_length] = '\0';  // Ensure null-termination

  // Call the function-under-test
  cJSON_bool result = cJSON_AddItemToObject(root, key, new_item);

  // Clean up
  free(key);
  cJSON_Delete(root);

  return 0;
}

#ifdef __cplusplus
}
#endif