#include <stdint.h>
#include <stdlib.h>
#include "/src/cjson/cJSON.h"  // Corrected the path to the cJSON header

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
  // Call the function-under-test
  cJSON *json_object = cJSON_CreateObject();

  // Check if the object was created successfully
  if (json_object != NULL) {
    // Perform operations on the created object
    // For example, add an item to the object
    cJSON_AddStringToObject(json_object, "key", "value");

    // Clean up and delete the created object
    cJSON_Delete(json_object);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif