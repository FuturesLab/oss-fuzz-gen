#include <stdint.h>
#include <stdlib.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
  // Call the function-under-test
  cJSON *array = cJSON_CreateArray();

  // Check if the array was created successfully
  if (array == NULL) {
    return 0;
  }

  // Attempt to parse the input data as JSON and add it to the array
  cJSON *parsed = cJSON_ParseWithLength((const char *)data, size);
  if (parsed != NULL) {
    cJSON_AddItemToArray(array, parsed);
  }

  // Clean up the created cJSON array
  cJSON_Delete(array);

  return 0;
}

#ifdef __cplusplus
}
#endif