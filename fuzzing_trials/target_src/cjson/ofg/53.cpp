#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
  cJSON *json = NULL;
  cJSON *detached_item = NULL;
  char *key = NULL;
  size_t key_length;

  if (size < 2) {
    return 0;
  }

  // Ensure the data is null-terminated for string operations
  uint8_t *mutable_data = (uint8_t *)malloc(size + 1);
  if (mutable_data == NULL) {
    return 0;
  }
  memcpy(mutable_data, data, size);
  mutable_data[size] = '\0';

  // Parse the data as a JSON object
  json = cJSON_Parse((const char *)mutable_data);
  if (json == NULL) {
    free(mutable_data);
    return 0;
  }

  // Determine key length from the first byte
  key_length = mutable_data[0] % (size - 1) + 1;

  // Allocate and copy key
  key = (char *)malloc(key_length + 1);
  if (key == NULL) {
    cJSON_Delete(json);
    free(mutable_data);
    return 0;
  }
  memcpy(key, mutable_data + 1, key_length);
  key[key_length] = '\0';

  // Call the function-under-test
  detached_item = cJSON_DetachItemFromObjectCaseSensitive(json, key);

  // Clean up
  if (detached_item != NULL) {
    cJSON_Delete(detached_item);
  }
  cJSON_Delete(json);
  free(mutable_data);
  free(key);

  return 0;
}

#ifdef __cplusplus
}
#endif