#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include this header for memcpy
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Create a cJSON object from the input data
  char *input_data = (char *)malloc(size + 1);
  if (input_data == NULL) {
    return 0;
  }
  
  memcpy(input_data, data, size);
  input_data[size] = '\0';

  cJSON *json = cJSON_Parse(input_data);

  // Clean up the created cJSON object
  if (json != NULL) {
    cJSON_Delete(json);
  }

  free(input_data);

  return 0;
}

#ifdef __cplusplus
}
#endif