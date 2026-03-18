#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
  cJSON *json_object = NULL;
  cJSON *detached_item = NULL;
  char *key = NULL;

  if (size < 2) {
    return 0;
  }

  // Ensure the data is null-terminated for string operations
  char *input_data = (char *)malloc(size + 1);
  if (input_data == NULL) {
    return 0;
  }
  memcpy(input_data, data, size);
  input_data[size] = '\0';

  // Parse the data into a cJSON object
  json_object = cJSON_Parse(input_data);
  if (json_object == NULL) {
    free(input_data);
    return 0;
  }

  // Use part of the input data as a key, ensuring it's null-terminated
  key = input_data;

  // Detach the item from the JSON object using the key
  detached_item = cJSON_DetachItemFromObject(json_object, key);

  // Clean up
  if (detached_item != NULL) {
    cJSON_Delete(detached_item);
  }
  cJSON_Delete(json_object);
  free(input_data);

  return 0;
}

#ifdef __cplusplus
}
#endif