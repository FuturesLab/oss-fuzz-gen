#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
  cJSON *json = NULL;
  cJSON *detached_item = NULL;
  char *json_string = NULL;
  int index;

  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  json_string = (char *)malloc(size + 1);
  if (json_string == NULL) {
    return 0;
  }

  memcpy(json_string, data, size);
  json_string[size] = '\0';

  json = cJSON_Parse(json_string);
  free(json_string);

  if (json == NULL || !cJSON_IsArray(json)) {
    if (json != NULL) {
      cJSON_Delete(json);
    }
    return 0;
  }

  index = size % cJSON_GetArraySize(json); // Ensure index is within bounds

  detached_item = cJSON_DetachItemFromArray(json, index);

  if (detached_item != NULL) {
    cJSON_Delete(detached_item);
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif