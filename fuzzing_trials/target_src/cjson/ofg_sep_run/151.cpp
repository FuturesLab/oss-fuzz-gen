#include <stdint.h>
#include <stdlib.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  cJSON_bool result = cJSON_IsBool(json);

  // Use the result to prevent any compiler optimizations that might skip the call
  if (result) {
    // Do something trivial to use the result
    (void)result;
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif