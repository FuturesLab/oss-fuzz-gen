#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
  if (size == 0) return 0;

  // Create a JSON array
  cJSON *array = cJSON_CreateArray();
  if (array == NULL) return 0;

  // Create a JSON item from the input data
  char *json_string = (char *)malloc(size + 1);
  if (json_string == NULL) {
    cJSON_Delete(array);
    return 0;
  }
  memcpy(json_string, data, size);
  json_string[size] = '\0';

  cJSON *item = cJSON_Parse(json_string);
  free(json_string);

  if (item == NULL) {
    cJSON_Delete(array);
    return 0;
  }

  // Add item reference to the array
  cJSON_bool result = cJSON_AddItemReferenceToArray(array, item);

  // Clean up
  cJSON_Delete(array);
  cJSON_Delete(item);

  return result;
}

#ifdef __cplusplus
}
#endif