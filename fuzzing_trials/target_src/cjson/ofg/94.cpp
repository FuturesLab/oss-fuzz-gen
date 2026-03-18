#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    // Ensure the string is null-terminated
    return 0;
  }

  // Convert the input data to a string
  const char *input_string = (const char *)data;

  // Call the function-under-test
  cJSON *json = cJSON_CreateStringReference(input_string);

  // Clean up the created cJSON object
  if (json != NULL) {
    cJSON_Delete(json);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif