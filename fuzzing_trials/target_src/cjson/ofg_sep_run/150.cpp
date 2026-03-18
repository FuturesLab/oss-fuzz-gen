#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>  // Added to fix the 'snprintf' undeclared identifier error

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
  cJSON *json_object;

  // Create a cJSON object
  json_object = cJSON_CreateObject();

  // Check if cJSON object creation was successful
  if (json_object == NULL) {
    return 0;
  }

  // Perform operations on the cJSON object
  // For example, add some key-value pairs
  if (size > 0) {
    // Use the input data to create a key-value pair
    char key[5];
    snprintf(key, sizeof(key), "key");
    cJSON_AddItemToObject(json_object, key, cJSON_CreateNumber((int)data[0]));
  }

  // Clean up and delete the cJSON object
  cJSON_Delete(json_object);

  return 0;
}

#ifdef __cplusplus
}
#endif