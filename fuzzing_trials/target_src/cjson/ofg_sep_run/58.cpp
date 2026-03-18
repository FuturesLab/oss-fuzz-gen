#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include this header for memcpy
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
  // Ensure the input data is not null and has a size greater than 0
  if (data == NULL || size == 0) {
    return 0;
  }

  // Attempt to parse the data as a JSON string
  char *json_string = (char *)malloc(size + 1);
  if (json_string == NULL) {
    return 0;
  }
  memcpy(json_string, data, size);
  json_string[size] = '\0';

  cJSON *json = cJSON_Parse(json_string);
  if (json != NULL) {
    // Clean up the created cJSON object
    cJSON_Delete(json);
  }

  free(json_string);
  return 0;
}

#ifdef __cplusplus
}
#endif