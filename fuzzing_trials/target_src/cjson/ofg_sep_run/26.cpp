#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Ensure the data is null-terminated for parsing
  char *json_data = (char *)malloc(size + 1);
  if (json_data == NULL) {
    return 0;
  }
  memcpy(json_data, data, size);
  json_data[size] = '\0';

  // Parse the input data to create a cJSON object
  cJSON *json = cJSON_Parse(json_data);

  // Free the allocated memory for json_data
  free(json_data);

  if (json == NULL) {
    return 0;
  }

  // Call the function-under-test
  cJSON_bool is_raw = cJSON_IsRaw(json);

  // Clean up the cJSON object
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif