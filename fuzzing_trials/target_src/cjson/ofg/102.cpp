#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0; // Ensure there's enough data for a meaningful test
  }

  // Create a root JSON object
  cJSON *root = cJSON_CreateObject();
  if (root == NULL) {
    return 0; // Failed to create root object
  }

  // Extract a key from the input data
  size_t key_len = data[0] % (size - 2); // Ensure key_len is within bounds
  char *key = (char *)malloc(key_len + 1);
  if (key == NULL) {
    cJSON_Delete(root);
    return 0; // Memory allocation failed
  }
  memcpy(key, data + 1, key_len);
  key[key_len] = '\0'; // Null-terminate the key

  // Create a new JSON item
  cJSON *item = cJSON_CreateNumber(data[size - 1]);
  if (item == NULL) {
    free(key);
    cJSON_Delete(root);
    return 0; // Failed to create item
  }

  // Add the item to the object
  cJSON_bool result = cJSON_AddItemToObject(root, key, item);

  // Clean up
  free(key);
  cJSON_Delete(root);

  return 0;
}

#ifdef __cplusplus
}
#endif