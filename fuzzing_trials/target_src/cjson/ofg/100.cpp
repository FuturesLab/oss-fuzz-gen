#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  cJSON_bool is_array = cJSON_IsArray(json);

  // Use the result to prevent compiler optimizations
  if (is_array) {
    cJSON *item = cJSON_GetArrayItem(json, 0);
    if (item != NULL) {
      cJSON_IsArray(item);
    }
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif