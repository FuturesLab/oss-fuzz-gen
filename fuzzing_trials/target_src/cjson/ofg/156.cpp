#include <stdint.h>
#include <stddef.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  // Convert the first byte of data to a boolean value
  cJSON_bool bool_value = (data[0] % 2 == 0) ? cJSON_True : cJSON_False;

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