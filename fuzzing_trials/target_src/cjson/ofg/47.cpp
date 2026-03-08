#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  int prebuffer_size = 1024; // Example buffer size
  cJSON_bool format = cJSON_True; // Example formatting choice

  char *printed_json = cJSON_PrintBuffered(json, prebuffer_size, format);
  if (printed_json != NULL) {
    free(printed_json);
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif