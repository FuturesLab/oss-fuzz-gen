#include <stdint.h>
#include <stdlib.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
  // Call the function-under-test
  cJSON *json_false = cJSON_CreateFalse();

  // Check if the function returned a non-NULL pointer
  if (json_false != NULL) {
    // Clean up the created cJSON object
    cJSON_Delete(json_false);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif