#include <stdint.h>
#include <stdlib.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
  // Create a new cJSON object
  cJSON *json_object = cJSON_CreateObject();
  
  // Check if the object creation was successful
  if (json_object == NULL) {
    return 0;
  }

  // Optionally, you can add some operations on the created object here
  // For instance, adding a dummy key-value pair if size is large enough
  if (size > 1) {
    char key[2] = { (char)data[0], '\0' };
    cJSON_AddStringToObject(json_object, key, "dummy_value");
  }

  // Clean up and delete the created cJSON object
  cJSON_Delete(json_object);

  return 0;
}

#ifdef __cplusplus
}
#endif