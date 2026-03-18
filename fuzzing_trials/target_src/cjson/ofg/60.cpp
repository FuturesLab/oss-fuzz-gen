#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include this header for memcpy
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
  // Convert the input data to a null-terminated string
  char *input = (char *)malloc(size + 1);
  if (input == NULL) {
    return 0;  // If memory allocation fails, return immediately
  }
  memcpy(input, data, size);
  input[size] = '\0';

  // Parse the input data as a cJSON object
  cJSON *json = cJSON_Parse(input);
  
  // Ensure that the parsed cJSON object is not NULL
  if (json != NULL) {
    // Perform any additional operations or checks if necessary

    // Clean up and delete the parsed cJSON object
    cJSON_Delete(json);
  }

  // Free the allocated memory for input
  free(input);

  return 0;
}

#ifdef __cplusplus
}
#endif