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
  int index;

  if (size < 5) // Ensure there's enough data for a JSON string and an index
    return 0;

  // Ensure the input data is null-terminated for JSON parsing
  if (data[size - 1] != '\0')
    return 0;

  // Parse the JSON from the input data
  json = cJSON_Parse((const char *)data);
  if (json == NULL)
    return 0;

  // Use the first 4 bytes of data to determine the index
  index = (int)(data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24));

  // Call the function under test
  cJSON_DeleteItemFromArray(json, index);

  // Clean up
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif