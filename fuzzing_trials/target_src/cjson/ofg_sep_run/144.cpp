#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Split the input data into two parts for two cJSON objects
  size_t mid = size / 2;
  const uint8_t *data1 = data;
  size_t size1 = mid;
  const uint8_t *data2 = data + mid;
  size_t size2 = size - mid;

  // Ensure both parts are null-terminated strings
  char *str1 = (char *)malloc(size1 + 1);
  char *str2 = (char *)malloc(size2 + 1);

  if (str1 == NULL || str2 == NULL) {
    free(str1);
    free(str2);
    return 0;
  }

  memcpy(str1, data1, size1);
  str1[size1] = '\0';
  memcpy(str2, data2, size2);
  str2[size2] = '\0';

  cJSON *json1 = cJSON_Parse(str1);
  cJSON *json2 = cJSON_Parse(str2);

  free(str1);
  free(str2);

  if (json1 == NULL || json2 == NULL) {
    cJSON_Delete(json1);
    cJSON_Delete(json2);
    return 0;
  }

  // Use the first byte of the input data to determine the cJSON_bool value
  cJSON_bool case_sensitive = data[0] % 2 == 0 ? cJSON_True : cJSON_False;

  // Call the function-under-test
  cJSON_bool result = cJSON_Compare(json1, json2, case_sensitive);

  // Clean up
  cJSON_Delete(json1);
  cJSON_Delete(json2);

  return 0;
}

#ifdef __cplusplus
}
#endif