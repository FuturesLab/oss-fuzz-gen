#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  // Parse the input data as a cJSON object
  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  // Call the function-under-test
  char *printed_json = cJSON_Print(json);

  // Ensure the printed JSON is not NULL
  if (printed_json != NULL) {
    // Free the printed JSON string
    free(printed_json);
  }

  // Clean up the cJSON object
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif