#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  const char *end_ptr = NULL;
  cJSON_bool require_null_termination = 1; // Use 1 for true, 0 for false

  // Call the function-under-test
  cJSON *json = cJSON_ParseWithOpts((const char *)data, &end_ptr, require_null_termination);

  // Clean up
  if (json != NULL) {
    cJSON_Delete(json);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif