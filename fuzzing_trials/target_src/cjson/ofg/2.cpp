#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
  cJSON *json;
  char *key;

  if (size < 2) {
    return 0;
  }

  // Ensure the data is null-terminated to be used as a string
  char *input = (char *)malloc(size + 1);
  if (input == NULL) {
    return 0;
  }
  memcpy(input, data, size);
  input[size] = '\0';

  // Parse the input data as a JSON object
  json = cJSON_Parse(input);
  if (json == NULL) {
    free(input);
    return 0;
  }

  // Use a portion of the input data as the key
  key = (char *)malloc(size / 2 + 1);
  if (key == NULL) {
    cJSON_Delete(json);
    free(input);
    return 0;
  }
  memcpy(key, data, size / 2);
  key[size / 2] = '\0';

  // Call the function-under-test
  cJSON_DeleteItemFromObject(json, key);

  // Clean up
  cJSON_Delete(json);
  free(input);
  free(key);

  return 0;
}

#ifdef __cplusplus
}
#endif