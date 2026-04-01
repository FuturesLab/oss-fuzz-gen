#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
  if (size == 0) return 0;

  // Create two cJSON objects
  cJSON *array = cJSON_CreateArray();
  cJSON *item = cJSON_ParseWithLength((const char *)data, size);

  if (array == NULL || item == NULL) {
    cJSON_Delete(array);
    cJSON_Delete(item);
    return 0;
  }

  // Call the function under test
  cJSON_bool result = cJSON_AddItemReferenceToArray(array, item);

  // Clean up
  cJSON_Delete(array);
  cJSON_Delete(item);

  return 0;
}

#ifdef __cplusplus
}
#endif