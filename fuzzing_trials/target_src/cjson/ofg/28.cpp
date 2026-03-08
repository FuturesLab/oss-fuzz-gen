#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  cJSON_bool result = cJSON_IsFalse(json);

  // Use the result in some way to prevent compiler optimizations from removing the call
  if (result) {
    // Do something if the result is true
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif