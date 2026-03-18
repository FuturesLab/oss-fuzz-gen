#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Create a root cJSON object
  cJSON *root = cJSON_CreateObject();
  if (root == NULL) {
    return 0;
  }

  // Extract a key and value from the input data
  size_t key_len = data[0] % size;
  size_t value_len = (data[1] % (size - key_len)) + 1;

  char *key = (char *)malloc(key_len + 1);
  char *value = (char *)malloc(value_len + 1);

  if (key == NULL || value == NULL) {
    cJSON_Delete(root);
    free(key);
    free(value);
    return 0;
  }

  memcpy(key, data + 1, key_len);
  key[key_len] = '\0';

  memcpy(value, data + 1 + key_len, value_len);
  value[value_len] = '\0';

  // Create a cJSON item for the value
  cJSON *item = cJSON_CreateString(value);
  if (item == NULL) {
    cJSON_Delete(root);
    free(key);
    free(value);
    return 0;
  }

  // Call the function-under-test
  cJSON_bool result = cJSON_AddItemToObjectCS(root, key, item);

  // Clean up
  cJSON_Delete(root);
  free(key);
  free(value);

  return result;
}

#ifdef __cplusplus
}
#endif