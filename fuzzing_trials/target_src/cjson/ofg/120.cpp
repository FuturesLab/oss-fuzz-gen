#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
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

  const char *parse_end = NULL;
  cJSON_bool require_null_terminated = 1; // or 0, try both

  // Call the function-under-test
  cJSON *json = cJSON_ParseWithOpts(input_data, &parse_end, require_null_terminated);

  // Clean up
  if (json != NULL) {
    cJSON_Delete(json);
  }
  free(input_data);

  return 0;
}

#ifdef __cplusplus
}
#endif