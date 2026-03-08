#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
  cJSON *json;
  char *printed_json = NULL;

  // Ensure the input data is null-terminated for parsing
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  // Parse the input data into a cJSON object
  json = cJSON_Parse((const char *)data);

  // If parsing is successful, print the cJSON object
  if (json != NULL) {
    printed_json = cJSON_Print(json);

    // Free the printed JSON string if it was allocated
    if (printed_json != NULL) {
      free(printed_json);
    }

    // Delete the cJSON object to prevent memory leaks
    cJSON_Delete(json);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif