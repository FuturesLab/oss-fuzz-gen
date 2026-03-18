#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
  if (size < sizeof(double)) {
    return 0;
  }

  // Create a cJSON object
  cJSON *json = cJSON_CreateObject();
  if (json == NULL) {
    return 0;
  }

  // Extract a double value from the input data
  double number;
  memcpy(&number, data, sizeof(double));

  // Call the function-under-test
  cJSON_SetNumberHelper(json, number);

  // Clean up
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif