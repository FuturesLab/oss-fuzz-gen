#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>  // Include this header for printf

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  cJSON_bool is_array = cJSON_IsArray(json);

  // Use the result of cJSON_IsArray to avoid compiler warnings about unused variables
  if (is_array) {
    // Do something if it's an array, for example, print a message
    // (In a real fuzzing scenario, you might not print anything, but this is just for demonstration)
    printf("The parsed JSON is an array.\n");
  } else {
    printf("The parsed JSON is not an array.\n");
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif