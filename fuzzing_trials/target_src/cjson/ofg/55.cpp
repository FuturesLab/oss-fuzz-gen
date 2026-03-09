#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
  char *json_string;

  // Ensure the input data is not empty and is null-terminated
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  // Allocate memory for the JSON string and copy the input data
  json_string = (char *)malloc(size + 1);
  if (json_string == NULL) {
    return 0;
  }

  memcpy(json_string, data, size);
  json_string[size] = '\0'; // Ensure null-termination

  // Call the function-under-test
  cJSON_Minify(json_string);

  // Free the allocated memory
  free(json_string);

  return 0;
}

#ifdef __cplusplus
}
#endif