#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
  // Ensure the data is null-terminated to be used as a string
  if (size == 0) {
    return 0;
  }

  // Convert the input data to a string
  char *input_string = (char *)malloc(size + 1);
  if (input_string == NULL) {
    return 0;
  }
  memcpy(input_string, data, size);
  input_string[size] = '\0';

  // Call the function-under-test
  cJSON *json = cJSON_CreateRaw(input_string);

  // Clean up
  if (json != NULL) {
    cJSON_Delete(json);
  }
  free(input_string);

  return 0;
}

#ifdef __cplusplus
}
#endif