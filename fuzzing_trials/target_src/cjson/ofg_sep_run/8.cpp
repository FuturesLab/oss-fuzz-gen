#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
  cJSON *json = NULL;
  cJSON *object_ref = NULL;

  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  object_ref = cJSON_CreateObjectReference(json);
  if (object_ref != NULL) {
    cJSON_Delete(object_ref);
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif