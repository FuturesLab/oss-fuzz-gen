#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  // Parse the input data to create a cJSON object
  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  // Create a dummy item to detach
  cJSON *item = cJSON_CreateString("dummy");

  // Attach the item to the JSON object to ensure it's part of the structure
  cJSON_AddItemToObject(json, "dummy_key", item);

  // Detach the item using cJSON_DetachItemViaPointer
  cJSON *detached_item = cJSON_DetachItemViaPointer(json, item);

  // Clean up
  cJSON_Delete(json);
  cJSON_Delete(detached_item);

  return 0;
}

#ifdef __cplusplus
}
#endif