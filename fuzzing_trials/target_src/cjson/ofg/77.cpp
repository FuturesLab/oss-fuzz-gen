#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  // Call the function-under-test
  cJSON_bool is_object = cJSON_IsObject(json);

  // Use the result to avoid any compiler optimizations that might skip the call
  if (is_object) {
    // Do something trivial with the result
    (void)is_object;
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif