#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

extern "C" int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
  if (size < sizeof(double) * 2) {
    return 0;
  }

  // Ensure that the size is a multiple of sizeof(double)
  size_t num_doubles = size / sizeof(double);
  if (num_doubles == 0) {
    return 0;
  }

  // Allocate memory for the double array
  double *double_array = (double *)malloc(num_doubles * sizeof(double));
  if (double_array == NULL) {
    return 0;
  }

  // Copy data into the double array
  memcpy(double_array, data, num_doubles * sizeof(double));

  // Call the function-under-test
  cJSON *json_array = cJSON_CreateDoubleArray(double_array, (int)num_doubles);

  // Clean up
  if (json_array != NULL) {
    cJSON_Delete(json_array);
  }
  free(double_array);

  return 0;
}