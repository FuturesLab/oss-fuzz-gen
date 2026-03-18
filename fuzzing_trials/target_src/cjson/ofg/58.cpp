#include <stdint.h>
#include <stddef.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
  // Ensure the data is not empty
  if (size == 0) {
    return 0;
  }

  // Call the function-under-test
  cJSON *json_null = cJSON_CreateNull();

  // Perform some basic operations on the created cJSON object
  if (json_null != NULL) {
    // Check if the type is cJSON_NULL
    if (json_null->type == cJSON_NULL) {
      // Do something with the cJSON object (e.g., print it)
      char *printed_json = cJSON_Print(json_null);
      if (printed_json != NULL) {
        // Normally you might do something with printed_json, but for fuzzing, just free it
        cJSON_free(printed_json);
      }
    }

    // Clean up and delete the cJSON object
    cJSON_Delete(json_null);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif