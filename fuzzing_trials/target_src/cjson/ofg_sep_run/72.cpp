#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
  if (size < 2) return 0; // Ensure there is enough data

  // Parse the input data to create a cJSON object
  cJSON *json_array = cJSON_Parse((const char *)data);
  if (json_array == NULL) return 0;

  // Create a new cJSON item to replace an existing item in the array
  cJSON *new_item = cJSON_CreateString("new_item");
  if (new_item == NULL) {
    cJSON_Delete(json_array);
    return 0;
  }

  // Use the second byte of data as the index for replacement
  int index = data[0] % cJSON_GetArraySize(json_array);

  // Call the function-under-test
  cJSON_ReplaceItemInArray(json_array, index, new_item);

  // Clean up
  cJSON_Delete(json_array);

  return 0;
}

#ifdef __cplusplus
}
#endif