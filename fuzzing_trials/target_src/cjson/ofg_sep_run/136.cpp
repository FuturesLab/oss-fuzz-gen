#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  cJSON_bool is_null = cJSON_IsNull(json);

  // Use the result of cJSON_IsNull to avoid compiler warnings about unused variables
  if (is_null) {
    // Do something trivial
    (void)is_null;
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif