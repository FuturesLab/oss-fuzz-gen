#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
  cJSON *json;
  char *buffer;
  int buffer_size;
  cJSON_bool formatted;

  // Ensure the input is large enough to contain at least one character for JSON parsing
  if (size < 2) {
    return 0;
  }

  // Parse the input data as a JSON object
  json = cJSON_ParseWithLength((const char *)data, size);
  if (json == NULL) {
    return 0;
  }

  // Set the buffer size to a reasonable value
  buffer_size = (int)size + 1; // +1 for null termination

  // Allocate memory for the buffer
  buffer = (char *)malloc(buffer_size);
  if (buffer == NULL) {
    cJSON_Delete(json);
    return 0;
  }

  // Set the formatted flag based on the first byte of the input data
  formatted = (data[0] % 2 == 0) ? cJSON_True : cJSON_False;

  // Call the function-under-test
  cJSON_PrintPreallocated(json, buffer, buffer_size, formatted);

  // Clean up
  free(buffer);
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif