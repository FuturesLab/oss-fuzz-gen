#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
  char *input_str;
  cJSON *json;

  // Ensure the input data is null-terminated
  input_str = (char *)malloc(size + 1);
  if (input_str == NULL) {
    return 0;
  }

  memcpy(input_str, data, size);
  input_str[size] = '\0';

  // Call the function-under-test
  json = cJSON_Parse(input_str);

  // Clean up
  if (json != NULL) {
    cJSON_Delete(json);
  }

  free(input_str);

  return 0;
}

#ifdef __cplusplus
}
#endif