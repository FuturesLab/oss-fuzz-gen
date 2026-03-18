#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
  cJSON *json;
  int index;

  if (size < 2) {
    return 0;
  }

  // Ensure the data is null-terminated for parsing
  char *json_data = (char *)malloc(size + 1);
  if (json_data == NULL) {
    return 0;
  }
  memcpy(json_data, data, size);
  json_data[size] = '\0';

  // Parse the JSON data
  json = cJSON_Parse(json_data);
  free(json_data);

  if (json == NULL) {
    return 0;
  }

  // Get the index from the data
  index = (int)data[0]; // Use the first byte as an index

  // Call the function under test
  cJSON_DeleteItemFromArray(json, index);

  // Clean up
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif