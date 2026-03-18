#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  cJSON_bool result = cJSON_IsTrue(json);

  // Use the result to avoid compiler warnings about unused variables
  (void)result;

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif