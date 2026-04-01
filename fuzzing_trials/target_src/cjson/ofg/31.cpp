#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Ensure the input data is null-terminated
  char *json_data = (char *)malloc(size + 1);
  if (json_data == NULL) {
    return 0;
  }
  memcpy(json_data, data, size);
  json_data[size] = '\0';

  // Parse the input data into a cJSON object
  cJSON *root = cJSON_Parse(json_data);
  free(json_data);

  if (root == NULL) {
    return 0;
  }

  // Create a new item to be detached
  cJSON *item = cJSON_CreateString("fuzz_item");
  if (item == NULL) {
    cJSON_Delete(root);
    return 0;
  }

  // Add the item to the root
  cJSON_AddItemToObject(root, "item", item);

  // Detach the item via pointer
  cJSON *detached_item = cJSON_DetachItemViaPointer(root, item);

  // Clean up
  if (detached_item != NULL) {
    cJSON_Delete(detached_item);
  }
  cJSON_Delete(root);

  return 0;
}

#ifdef __cplusplus
}
#endif