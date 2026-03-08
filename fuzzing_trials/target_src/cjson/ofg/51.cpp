#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
  cJSON *json;
  cJSON *item;
  int index;

  if (size < 1) {
    return 0;
  }

  // Ensure the data is null-terminated for cJSON_Parse
  unsigned char *null_terminated_data = (unsigned char *)malloc(size + 1);
  if (null_terminated_data == NULL) {
    return 0;
  }
  memcpy(null_terminated_data, data, size);
  null_terminated_data[size] = '\0';

  json = cJSON_Parse((const char *)null_terminated_data);
  free(null_terminated_data);

  if (json == NULL) {
    return 0;
  }

  // Use the first byte of data to determine the index
  index = (int)data[0];

  item = cJSON_GetArrayItem(json, index);

  // Clean up
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif