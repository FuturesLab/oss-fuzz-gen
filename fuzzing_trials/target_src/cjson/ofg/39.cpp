#include <stdint.h>
#include <stdlib.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
  // Call the function-under-test
  cJSON *array = cJSON_CreateArray();

  // Ensure the array is not NULL before proceeding
  if (array != NULL) {
    // Optionally, you can add some elements to the array for further testing
    // For example, adding a string and a number
    cJSON_AddItemToArray(array, cJSON_CreateString("test"));
    cJSON_AddItemToArray(array, cJSON_CreateNumber(123));

    // Clean up the created cJSON array
    cJSON_Delete(array);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif