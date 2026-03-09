#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  cJSON_bool is_string = cJSON_IsString(json);

  // Use the result to avoid any compiler optimizations that might skip the call
  if (is_string) {
    // Do something trivial with the result
    cJSON *string_item = cJSON_CreateString("example");
    if (string_item != NULL) {
      cJSON_Delete(string_item);
    }
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif