#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Ensure the input data is null-terminated for string operations
  char *input_copy = (char *)malloc(size + 1);
  if (input_copy == NULL) {
    return 0;
  }

  memcpy(input_copy, data, size);
  input_copy[size] = '\0';

  // Parse the input data as a JSON object
  cJSON *json = cJSON_Parse(input_copy);
  if (json == NULL) {
    free(input_copy);
    return 0;
  }

  // Use a portion of the input data as the key for cJSON_HasObjectItem
  const char *key = input_copy + (size / 2);

  // Call the function-under-test
  cJSON_bool result = cJSON_HasObjectItem(json, key);

  // Clean up
  cJSON_Delete(json);
  free(input_copy);

  return 0;
}

#ifdef __cplusplus
}
#endif