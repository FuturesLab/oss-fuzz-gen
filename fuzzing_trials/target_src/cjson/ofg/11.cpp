#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
  // Ensure the data is null-terminated
  char *json_data = (char *)malloc(size + 1);
  if (json_data == NULL) {
    return 0;
  }
  
  memcpy(json_data, data, size);
  json_data[size] = '\0';

  // Parse the JSON data
  cJSON *json = cJSON_Parse(json_data);

  // If parsing was successful, delete the cJSON object
  if (json != NULL) {
    cJSON_Delete(json);
  }

  // Free the allocated memory
  free(json_data);

  return 0;
}

#ifdef __cplusplus
}
#endif