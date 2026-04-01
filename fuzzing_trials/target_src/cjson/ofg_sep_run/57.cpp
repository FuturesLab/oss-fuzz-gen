#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
  // Call the function-under-test
  cJSON *json = cJSON_CreateNull();

  // Check if the cJSON object was created successfully
  if (json != NULL) {
    // Perform operations on the created cJSON object if needed
    // For this harness, we will just delete it to check for any memory issues
    cJSON_Delete(json);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif