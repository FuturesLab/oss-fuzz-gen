#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
  // Ensure the input data is null-terminated
  if (size == 0) {
    return 0;
  }

  // Create a null-terminated copy of the data
  char *null_terminated_data = (char *)malloc(size + 1);
  if (null_terminated_data == NULL) {
    return 0;
  }
  memcpy(null_terminated_data, data, size);
  null_terminated_data[size] = '\0';

  // Parse the input data as a JSON object
  cJSON *json = cJSON_Parse(null_terminated_data);

  // If parsing was successful, delete the JSON object
  if (json != NULL) {
    cJSON_Delete(json);
  }

  // Free the allocated memory
  free(null_terminated_data);

  return 0;
}

#ifdef __cplusplus
}
#endif