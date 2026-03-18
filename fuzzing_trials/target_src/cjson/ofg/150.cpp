#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
  cJSON *json_object = cJSON_CreateObject();
  
  if (json_object == NULL) {
    return 0;
  }

  // Here, you could add additional fuzzing logic to manipulate the JSON object
  // For example, adding items to the JSON object using cJSON_AddItemToObject

  // Clean up
  cJSON_Delete(json_object);

  return 0;
}

#ifdef __cplusplus
}
#endif