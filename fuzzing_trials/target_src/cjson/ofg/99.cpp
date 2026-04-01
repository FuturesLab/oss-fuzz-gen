#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  // Call the function-under-test
  cJSON_bool is_array = cJSON_IsArray(json);

  // Clean up
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif