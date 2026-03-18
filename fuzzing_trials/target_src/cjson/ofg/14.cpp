#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
  if (size < sizeof(float)) {
    return 0;
  }

  int num_floats = size / sizeof(float);
  float *float_array = (float *)malloc(num_floats * sizeof(float));
  if (float_array == NULL) {
    return 0;
  }

  memcpy(float_array, data, num_floats * sizeof(float));

  cJSON *json_array = cJSON_CreateFloatArray(float_array, num_floats);

  if (json_array != NULL) {
    cJSON_Delete(json_array);
  }

  free(float_array);

  return 0;
}

#ifdef __cplusplus
}
#endif