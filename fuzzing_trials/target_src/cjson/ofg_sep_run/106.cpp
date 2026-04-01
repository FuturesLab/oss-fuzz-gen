#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
  char *input_string;
  cJSON *json_raw;

  // Ensure the input data is null-terminated
  input_string = (char *)malloc(size + 1);
  if (input_string == NULL) {
    return 0;
  }
  memcpy(input_string, data, size);
  input_string[size] = '\0';

  // Call the function-under-test
  json_raw = cJSON_CreateRaw(input_string);

  // Clean up
  if (json_raw != NULL) {
    cJSON_Delete(json_raw);
  }
  free(input_string);

  return 0;
}

#ifdef __cplusplus
}
#endif