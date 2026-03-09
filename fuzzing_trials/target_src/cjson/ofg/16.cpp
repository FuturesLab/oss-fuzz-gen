#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  cJSON *array_reference = cJSON_CreateArrayReference(json);

  if (array_reference != NULL) {
    cJSON_Delete(array_reference);
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif