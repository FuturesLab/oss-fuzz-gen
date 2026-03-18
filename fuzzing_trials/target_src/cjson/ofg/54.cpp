#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Ensure the input data is null-terminated
  char *input_data = (char *)malloc(size + 1);
  if (input_data == NULL) {
    return 0;
  }
  memcpy(input_data, data, size);
  input_data[size] = '\0';

  // Parse the input data as a JSON object
  cJSON *json = cJSON_Parse(input_data);
  if (json == NULL) {
    free(input_data);
    return 0;
  }

  // Use the first byte of data as the key length
  size_t key_length = (size_t)data[0] % (size - 1) + 1;

  // Ensure the key is null-terminated
  char *key = (char *)malloc(key_length + 1);
  if (key == NULL) {
    cJSON_Delete(json);
    free(input_data);
    return 0;
  }
  memcpy(key, data + 1, key_length);
  key[key_length] = '\0';

  // Call the function under test
  cJSON *detached_item = cJSON_DetachItemFromObjectCaseSensitive(json, key);

  // Clean up
  if (detached_item != NULL) {
    cJSON_Delete(detached_item);
  }
  cJSON_Delete(json);
  free(input_data);
  free(key);

  return 0;
}

#ifdef __cplusplus
}
#endif