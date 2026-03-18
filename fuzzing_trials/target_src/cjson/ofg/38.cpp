#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
  cJSON *json = NULL;
  cJSON *detached_item = NULL;
  char *key = NULL;

  if (size < 2) {
    return 0;
  }

  // Ensure the data is null-terminated for safe string operations
  char *input_data = (char *)malloc(size + 1);
  if (input_data == NULL) {
    return 0;
  }
  memcpy(input_data, data, size);
  input_data[size] = '\0';

  // Parse the input data into a cJSON object
  json = cJSON_Parse(input_data);
  if (json == NULL) {
    free(input_data);
    return 0;
  }

  // Use part of the input data as a key for detaching an item
  key = input_data;
  
  // Detach an item from the JSON object
  detached_item = cJSON_DetachItemFromObject(json, key);

  // Clean up
  if (detached_item != NULL) {
    cJSON_Delete(detached_item);
  }
  cJSON_Delete(json);
  free(input_data);

  return 0;
}

#ifdef __cplusplus
}
#endif