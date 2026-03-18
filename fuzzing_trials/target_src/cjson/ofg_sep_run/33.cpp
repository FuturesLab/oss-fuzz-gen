#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  const char *input_string = (const char *)data;

  cJSON *json_string = cJSON_CreateString(input_string);

  if (json_string != NULL) {
    cJSON_Delete(json_string);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif