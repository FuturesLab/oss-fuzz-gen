#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
  if (size < sizeof(double)) {
    return 0;
  }

  int num_doubles = size / sizeof(double);
  double *double_array = (double *)malloc(num_doubles * sizeof(double));
  if (double_array == NULL) {
    return 0;
  }

  memcpy(double_array, data, num_doubles * sizeof(double));

  cJSON *json_array = cJSON_CreateDoubleArray(double_array, num_doubles);

  if (json_array != NULL) {
    cJSON_Delete(json_array);
  }

  free(double_array);

  return 0;
}

#ifdef __cplusplus
}
#endif