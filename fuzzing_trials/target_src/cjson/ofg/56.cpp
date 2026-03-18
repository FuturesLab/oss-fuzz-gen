#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
  char *input;

  if (size == 0) {
    return 0;
  }

  // Allocate memory and copy the input data
  input = (char *)malloc(size + 1);
  if (input == NULL) {
    return 0;
  }
  memcpy(input, data, size);
  input[size] = '\0';  // Ensure null-termination

  // Call the function-under-test
  cJSON_Minify(input);

  // Free the allocated memory
  free(input);

  return 0;
}

#ifdef __cplusplus
}
#endif