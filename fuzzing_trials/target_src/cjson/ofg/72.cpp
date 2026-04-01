#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Create a JSON array
  cJSON *json_array = cJSON_CreateArray();
  if (json_array == NULL) {
    return 0;
  }

  // Create a JSON item to replace
  cJSON *new_item = cJSON_CreateString("new_item");
  if (new_item == NULL) {
    cJSON_Delete(json_array);
    return 0;
  }

  // Add a few items to the array
  for (int i = 0; i < 5; ++i) {
    cJSON *item = cJSON_CreateNumber(i);
    if (item == NULL) {
      cJSON_Delete(new_item);
      cJSON_Delete(json_array);
      return 0;
    }
    cJSON_AddItemToArray(json_array, item);
  }

  // Use the first byte of data as the index to replace
  int index = data[0] % cJSON_GetArraySize(json_array);

  // Call the function to fuzz
  cJSON_bool result = cJSON_ReplaceItemInArray(json_array, index, new_item);

  // Clean up
  cJSON_Delete(json_array);

  return 0;
}

#ifdef __cplusplus
}
#endif