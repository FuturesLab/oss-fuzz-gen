#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Create a cJSON array
  cJSON *array = cJSON_CreateArray();
  if (array == NULL) {
    return 0;
  }

  // Parse the input data as a cJSON object
  cJSON *item = cJSON_ParseWithLength((const char*)data, size);
  if (item == NULL) {
    cJSON_Delete(array);
    return 0;
  }

  // Add a reference to the item in the array
  cJSON_bool result = cJSON_AddItemReferenceToArray(array, item);

  // Clean up
  cJSON_Delete(array);
  cJSON_Delete(item);

  return 0;
}

#ifdef __cplusplus
}
#endif