#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

extern "C" int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
  // Ensure the input data is null-terminated to be used as a string
  char *inputString = (char *)malloc(size + 1);
  if (inputString == NULL) {
    return 0;
  }
  memcpy(inputString, data, size);
  inputString[size] = '\0';

  // Call the function-under-test
  cJSON *json = cJSON_CreateStringReference(inputString);

  // Clean up
  if (json != NULL) {
    cJSON_Delete(json);
  }
  free(inputString);

  return 0;
}

#ifdef __cplusplus
}
#endif