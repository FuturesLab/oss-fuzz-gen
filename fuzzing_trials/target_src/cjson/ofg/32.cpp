#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Ensure the data is null-terminated for JSON parsing
  unsigned char *json_data = (unsigned char *)malloc(size + 1);
  if (json_data == NULL) {
    return 0;
  }
  memcpy(json_data, data, size);
  json_data[size] = '\0';

  // Parse the JSON data
  cJSON *root = cJSON_Parse((const char *)json_data);
  if (root == NULL) {
    free(json_data);
    return 0;
  }

  // Create a dummy item to detach
  cJSON *dummy_item = cJSON_CreateString("dummy");
  if (dummy_item == NULL) {
    cJSON_Delete(root);
    free(json_data);
    return 0;
  }

  // Add the dummy item to the root
  cJSON_AddItemToObject(root, "dummy_key", dummy_item);

  // Detach the dummy item
  cJSON *detached_item = cJSON_DetachItemViaPointer(root, dummy_item);

  // Clean up
  cJSON_Delete(detached_item);
  cJSON_Delete(root);
  free(json_data);

  return 0;
}

#ifdef __cplusplus
}
#endif