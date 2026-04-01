#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
  // Ensure the input data is not empty
  if (size == 0) {
    return 0;
  }

  // Create a root cJSON array
  cJSON *root_array = cJSON_CreateArray();
  if (root_array == NULL) {
    return 0;
  }

  // Parse the input data into a cJSON object
  cJSON *item = cJSON_ParseWithLength((const char *)data, size);
  if (item == NULL) {
    cJSON_Delete(root_array);
    return 0;
  }

  // Add a reference of the parsed item to the root array
  cJSON_bool result = cJSON_AddItemReferenceToArray(root_array, item);

  // Clean up
  cJSON_Delete(root_array);
  cJSON_Delete(item);

  return 0;
}

#ifdef __cplusplus
}
#endif