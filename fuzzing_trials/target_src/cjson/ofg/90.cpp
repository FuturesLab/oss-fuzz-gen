#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include this header for memcpy
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
  // Ensure the input data is null-terminated to safely use it as a string
  char *input = (char *)malloc(size + 1);
  if (input == NULL) {
    return 0;
  }
  memcpy(input, data, size);
  input[size] = '\0';

  // Call the function-under-test with the input data
  cJSON *json = cJSON_Parse(input);

  // Clean up the created cJSON object
  if (json != NULL) {
    cJSON_Delete(json);
  }

  free(input);
  return 0;
}

#ifdef __cplusplus
}
#endif