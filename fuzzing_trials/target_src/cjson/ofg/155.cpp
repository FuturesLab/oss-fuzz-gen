#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  // Use the first byte of data to determine the boolean value
  cJSON_bool bool_value = (cJSON_bool)(data[0] % 2);

  // Call the function-under-test
  cJSON *json_bool = cJSON_CreateBool(bool_value);

  // Clean up the created cJSON object
  if (json_bool != NULL) {
    cJSON_Delete(json_bool);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif