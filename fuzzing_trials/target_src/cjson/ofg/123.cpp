#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  // Split the input data into three parts for the three cJSON objects
  size_t part_size = size / 3;
  size_t remainder = size % 3;

  const uint8_t *data1 = data;
  const uint8_t *data2 = data + part_size;
  const uint8_t *data3 = data + 2 * part_size;

  // Ensure each part is null-terminated for parsing
  char *json_str1 = (char *)malloc(part_size + 1);
  char *json_str2 = (char *)malloc(part_size + 1);
  char *json_str3 = (char *)malloc(part_size + remainder + 1);

  if (!json_str1 || !json_str2 || !json_str3) {
    free(json_str1);
    free(json_str2);
    free(json_str3);
    return 0;
  }

  memcpy(json_str1, data1, part_size);
  memcpy(json_str2, data2, part_size);
  memcpy(json_str3, data3, part_size + remainder);

  json_str1[part_size] = '\0';
  json_str2[part_size] = '\0';
  json_str3[part_size + remainder] = '\0';

  cJSON *json1 = cJSON_Parse(json_str1);
  cJSON *json2 = cJSON_Parse(json_str2);
  cJSON *json3 = cJSON_Parse(json_str3);

  if (json1 && json2 && json3) {
    cJSON_ReplaceItemViaPointer(json1, json2, json3);
  }

  cJSON_Delete(json1);
  cJSON_Delete(json2);
  cJSON_Delete(json3);

  free(json_str1);
  free(json_str2);
  free(json_str3);

  return 0;
}

#ifdef __cplusplus
}
#endif