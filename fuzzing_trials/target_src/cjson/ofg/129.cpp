#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
  cJSON *json_array = NULL;
  cJSON *detached_item = NULL;
  int index;

  // Ensure the input data is not empty and null-terminated
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  // Parse the input data into a cJSON object
  json_array = cJSON_Parse((const char *)data);
  if (json_array == NULL) {
    return 0;
  }

  // Ensure the parsed object is an array
  if (!cJSON_IsArray(json_array)) {
    cJSON_Delete(json_array);
    return 0;
  }

  // Use a simple strategy to determine the index
  index = (int)(data[0] % cJSON_GetArraySize(json_array));

  // Call the function-under-test
  detached_item = cJSON_DetachItemFromArray(json_array, index);

  // Clean up
  if (detached_item != NULL) {
    cJSON_Delete(detached_item);
  }
  cJSON_Delete(json_array);

  return 0;
}

#ifdef __cplusplus
}
#endif