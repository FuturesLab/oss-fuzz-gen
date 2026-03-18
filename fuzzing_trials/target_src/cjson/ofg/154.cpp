#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Create a cJSON object
  cJSON *json = cJSON_CreateObject();
  if (json == NULL) {
    return 0;
  }

  // Ensure the input data is null-terminated
  char *input_string = (char *)malloc(size + 1);
  if (input_string == NULL) {
    cJSON_Delete(json);
    return 0;
  }
  memcpy(input_string, data, size);
  input_string[size] = '\0';

  // Call the function-under-test
  char *result = cJSON_SetValuestring(json, input_string);

  // Clean up
  free(input_string);
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif