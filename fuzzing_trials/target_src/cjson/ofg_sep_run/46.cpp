#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
  cJSON *json;
  char *printed_json = NULL;

  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  json = cJSON_Parse((const char *)data);

  if (json == NULL) {
    return 0;
  }

  printed_json = cJSON_PrintUnformatted(json);

  if (printed_json != NULL) {
    free(printed_json);
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif