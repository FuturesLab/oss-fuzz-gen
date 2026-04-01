#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
  cJSON *json;
  char *unformatted_json = NULL;

  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  json = cJSON_Parse((const char *)data);

  if (json == NULL) {
    return 0;
  }

  unformatted_json = cJSON_PrintUnformatted(json);

  if (unformatted_json != NULL) {
    free(unformatted_json);
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif