#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  // Ensure the data is null-terminated for JSON parsing
  char *json_data = (char *)malloc(size + 1);
  if (json_data == NULL) {
    return 0;
  }
  memcpy(json_data, data, size);
  json_data[size] = '\0';

  // Parse the input data as a JSON array
  cJSON *json_array = cJSON_Parse(json_data);
  free(json_data);

  if (json_array == NULL || !cJSON_IsArray(json_array)) {
    cJSON_Delete(json_array);
    return 0;
  }

  // Use the first byte of data to determine the index to delete
  int index_to_delete = data[0] % cJSON_GetArraySize(json_array);

  // Call the function-under-test
  cJSON_DeleteItemFromArray(json_array, index_to_delete);

  // Clean up
  cJSON_Delete(json_array);

  return 0;
}

#ifdef __cplusplus
}
#endif