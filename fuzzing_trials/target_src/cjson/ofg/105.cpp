#include <cstdint>
#include <cstdlib>
#include <cstring>

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
  // Ensure the input data is null-terminated
  char *input = (char *)malloc(size + 1);
  if (input == NULL) {
    return 0;
  }
  memcpy(input, data, size);
  input[size] = '\0';

  // Call the function-under-test
  cJSON *json = cJSON_CreateRaw(input);

  // Clean up
  if (json != NULL) {
    cJSON_Delete(json);
  }
  free(input);

  return 0;
}

#ifdef __cplusplus
}
#endif