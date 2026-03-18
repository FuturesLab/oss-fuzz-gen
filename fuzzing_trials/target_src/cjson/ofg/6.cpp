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

  // Ensure the data is null-terminated for cJSON_Parse
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  // Parse the input data into a cJSON object
  json = cJSON_Parse((const char *)data);

  if (json == NULL) {
    return 0;
  }

  // Call the function-under-test
  printed_json = cJSON_Print(json);

  // Free the printed JSON string if it was created
  if (printed_json != NULL) {
    free(printed_json);
  }

  // Delete the cJSON object to free memory
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif