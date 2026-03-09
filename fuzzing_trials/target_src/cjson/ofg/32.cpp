#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
  if (size == 0) return 0;

  // Create a root JSON object
  cJSON *root = cJSON_CreateObject();
  if (root == NULL) return 0;

  // Create a child JSON object from input data
  cJSON *child = cJSON_ParseWithLength((const char *)data, size);
  if (child == NULL) {
    cJSON_Delete(root);
    return 0;
  }

  // Add the child to the root
  cJSON_AddItemToObject(root, "child", child);

  // Detach the child item via pointer
  cJSON *detached_item = cJSON_DetachItemViaPointer(root, child);

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