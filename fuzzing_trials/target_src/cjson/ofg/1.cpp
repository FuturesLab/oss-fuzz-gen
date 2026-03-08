#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
  cJSON *json;
  char *key;

  if (size < 2) {
    return 0;
  }

  // Ensure the data is null-terminated for string operations
  char *data_copy = (char *)malloc(size + 1);
  if (data_copy == NULL) {
    return 0;
  }
  memcpy(data_copy, data, size);
  data_copy[size] = '\0';

  // Parse the JSON object from the data
  json = cJSON_Parse(data_copy);
  if (json == NULL) {
    free(data_copy);
    return 0;
  }

  // Use part of the data as a key for the JSON object
  key = data_copy;

  // Call the function-under-test
  cJSON_DeleteItemFromObject(json, key);

  // Clean up
  cJSON_Delete(json);
  free(data_copy);

  return 0;
}

#ifdef __cplusplus
}
#endif