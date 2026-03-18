#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  const char *parse_end = NULL;
  cJSON_bool require_null_termination = (data[0] % 2 == 0) ? cJSON_True : cJSON_False;

  // Ensure the input data is null-terminated if required
  char *input_data = (char *)malloc(size + 1);
  if (input_data == NULL) {
    return 0;
  }
  memcpy(input_data, data, size);
  input_data[size] = '\0';

  cJSON *json = cJSON_ParseWithLengthOpts(input_data, size, &parse_end, require_null_termination);

  if (json != NULL) {
    cJSON_Delete(json);
  }

  free(input_data);

  return 0;
}

#ifdef __cplusplus
}
#endif