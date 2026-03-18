#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
  if (size < 3) return 0; // Ensure there's enough data for parsing

  // Split the input data into three parts for each cJSON object
  size_t part_size = size / 3;
  size_t remainder = size % 3;

  const uint8_t *first_part = data;
  const uint8_t *second_part = data + part_size;
  const uint8_t *third_part = data + 2 * part_size;

  // Parse the first part into a cJSON object
  cJSON *json1 = cJSON_ParseWithLength((const char *)first_part, part_size);
  if (json1 == NULL) return 0;

  // Parse the second part into a cJSON object
  cJSON *json2 = cJSON_ParseWithLength((const char *)second_part, part_size + (remainder > 0 ? 1 : 0));
  if (json2 == NULL) {
    cJSON_Delete(json1);
    return 0;
  }

  // Parse the third part into a cJSON object
  cJSON *json3 = cJSON_ParseWithLength((const char *)third_part, part_size + (remainder > 1 ? 1 : 0));
  if (json3 == NULL) {
    cJSON_Delete(json1);
    cJSON_Delete(json2);
    return 0;
  }

  // Call the function-under-test
  cJSON_ReplaceItemViaPointer(json1, json2, json3);

  // Clean up
  cJSON_Delete(json1);
  cJSON_Delete(json2);
  cJSON_Delete(json3);

  return 0;
}

#ifdef __cplusplus
}
#endif