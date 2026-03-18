#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  cJSON_bool result = cJSON_IsString(json);

  // Use the result to prevent compiler optimizations
  if (result) {
    // Do something if it is a string
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif