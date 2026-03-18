#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Create a root cJSON object
  cJSON *root = cJSON_CreateObject();
  if (root == NULL) {
    return 0;
  }

  // Create a new cJSON item to be inserted
  cJSON *new_item = cJSON_CreateString("new_value");
  if (new_item == NULL) {
    cJSON_Delete(root);
    return 0;
  }

  // Extract a key from the data
  size_t key_length = data[0] % (size - 1) + 1; // Ensure key length is valid
  char *key = (char *)malloc(key_length + 1);
  if (key == NULL) {
    cJSON_Delete(root);
    cJSON_Delete(new_item);
    return 0;
  }
  memcpy(key, data + 1, key_length);
  key[key_length] = '\0';

  // Add an initial item to the root object with the same key
  cJSON_AddItemToObject(root, key, cJSON_CreateString("initial_value"));

  // Attempt to replace the item in the object
  cJSON_bool result = cJSON_ReplaceItemInObject(root, key, new_item);

  // Clean up
  free(key);
  cJSON_Delete(root);

  return 0;
}

#ifdef __cplusplus
}
#endif