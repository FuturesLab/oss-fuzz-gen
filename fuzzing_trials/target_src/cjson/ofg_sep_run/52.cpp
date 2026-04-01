#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Ensure the input data is null-terminated
  char *input_data = (char *)malloc(size + 1);
  if (input_data == NULL) {
    return 0;
  }
  memcpy(input_data, data, size);
  input_data[size] = '\0';

  // Parse the input data as a cJSON object
  cJSON *json = cJSON_Parse(input_data);
  free(input_data);

  if (json == NULL) {
    return 0;
  }

  // Ensure the cJSON object is an array
  if (!cJSON_IsArray(json)) {
    cJSON_Delete(json);
    return 0;
  }

  // Use a fixed index for demonstration purposes
  int index = size % 10; // Choose an index based on the input size

  // Call the function-under-test
  cJSON *item = cJSON_GetArrayItem(json, index);

  // Clean up
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif