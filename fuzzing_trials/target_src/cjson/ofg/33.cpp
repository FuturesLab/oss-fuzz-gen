#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Ensure the data is null-terminated to be used as a string.
  char *input_string = (char *)malloc(size + 1);
  if (input_string == NULL) {
    return 0;
  }

  memcpy(input_string, data, size);
  input_string[size] = '\0';

  // Call the function-under-test
  cJSON *json_string = cJSON_CreateString(input_string);

  // Clean up
  if (json_string != NULL) {
    cJSON_Delete(json_string);
  }
  free(input_string);

  return 0;
}

#ifdef __cplusplus
}
#endif