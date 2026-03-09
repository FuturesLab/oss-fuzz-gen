#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
  cJSON *json;
  char *buffer;
  int buffer_size;
  cJSON_bool formatted;
  cJSON_bool result;

  if (size < 5) // Ensure there is enough data for parsing and options
    return 0;

  // Parse JSON from the input data
  json = cJSON_ParseWithOpts((const char *)data, NULL, 1);
  if (json == NULL)
    return 0;

  // Determine buffer size and formatted option from the input data
  buffer_size = (int)data[0] + 1; // Ensure buffer size is at least 1
  formatted = data[1] % 2 == 0 ? 1 : 0; // Use the second byte to decide formatting

  // Allocate buffer for preallocated printing
  buffer = (char *)malloc(buffer_size);
  if (buffer == NULL) {
    cJSON_Delete(json);
    return 0;
  }

  // Call the function-under-test
  result = cJSON_PrintPreallocated(json, buffer, buffer_size, formatted);

  // Clean up
  free(buffer);
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif