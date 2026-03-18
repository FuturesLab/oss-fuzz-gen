#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
  char *input_string;
  cJSON *json_string_reference;

  if (size == 0)
    return 0;

  // Ensure the input data is null-terminated
  input_string = (char *)malloc(size + 1);
  if (input_string == NULL)
    return 0;

  memcpy(input_string, data, size);
  input_string[size] = '\0';

  // Call the function-under-test
  json_string_reference = cJSON_CreateStringReference(input_string);

  // Clean up
  cJSON_Delete(json_string_reference);
  free(input_string);

  return 0;
}

#ifdef __cplusplus
}
#endif