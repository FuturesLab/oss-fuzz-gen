#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
  cJSON *json;
  cJSON *array;
  char *json_string;
  int index;

  if (size < 2) {
    return 0;
  }

  // Ensure the data is null-terminated for parsing
  json_string = (char *)malloc(size + 1);
  if (json_string == NULL) {
    return 0;
  }
  memcpy(json_string, data, size);
  json_string[size] = '\0';

  // Parse the input data as a JSON object
  json = cJSON_Parse(json_string);
  free(json_string);

  if (json == NULL) {
    return 0;
  }

  // Create a JSON array to work with
  array = cJSON_CreateArray();
  if (array == NULL) {
    cJSON_Delete(json);
    return 0;
  }

  // Add the parsed JSON object to the array
  cJSON_AddItemToArray(array, json);

  // Use the first byte of data to determine the index to delete
  index = data[0] % cJSON_GetArraySize(array);

  // Call the function-under-test
  cJSON_DeleteItemFromArray(array, index);

  // Clean up
  cJSON_Delete(array);

  return 0;
}

#ifdef __cplusplus
}
#endif