#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
  cJSON *json;
  const char *error_ptr;

  // Check if the input data is valid for parsing
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  // Parse the input data as a JSON object
  json = cJSON_Parse((const char *)data);

  // Retrieve the error pointer
  error_ptr = cJSON_GetErrorPtr();

  // If parsing failed, error_ptr should point to the error location
  if (json == NULL && error_ptr != NULL) {
    // You can log or handle the error pointer as needed
  }

  // Clean up
  if (json != NULL) {
    cJSON_Delete(json);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif