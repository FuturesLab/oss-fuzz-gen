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

  cJSON_bool result = cJSON_IsArray(json);

  cJSON_Delete(json);

  return result;
}

#ifdef __cplusplus
}
#endif