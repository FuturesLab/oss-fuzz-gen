#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  // Split the input data into three parts for fuzzing the function parameters
  size_t part1_size = size / 3;
  size_t part2_size = (size - part1_size) / 2;
  size_t part3_size = size - part1_size - part2_size;

  const char *key = (const char *)malloc(part2_size + 1);
  const char *raw_value = (const char *)malloc(part3_size + 1);

  if (!key || !raw_value) {
    free((void *)key);
    free((void *)raw_value);
    return 0;
  }

  memcpy((void *)key, data + part1_size, part2_size);
  memcpy((void *)raw_value, data + part1_size + part2_size, part3_size);

  ((char *)key)[part2_size] = '\0';
  ((char *)raw_value)[part3_size] = '\0';

  // Create a cJSON object to use as the parent
  cJSON *parent = cJSON_CreateObject();
  if (!parent) {
    free((void *)key);
    free((void *)raw_value);
    return 0;
  }

  // Call the function-under-test
  cJSON *result = cJSON_AddRawToObject(parent, key, raw_value);

  // Clean up
  cJSON_Delete(parent);
  free((void *)key);
  free((void *)raw_value);

  return 0;
}

#ifdef __cplusplus
}
#endif