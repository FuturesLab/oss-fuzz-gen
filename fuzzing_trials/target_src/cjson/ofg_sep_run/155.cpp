#include <stdint.h>
#include <stdlib.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  // Use the first byte of data to determine the boolean value
  cJSON_bool bool_value = (data[0] % 2 == 0) ? cJSON_False : cJSON_True;

  // Create a cJSON boolean object
  cJSON *json_bool = cJSON_CreateBool(bool_value);

  // Clean up
  if (json_bool != NULL) {
    cJSON_Delete(json_bool);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif