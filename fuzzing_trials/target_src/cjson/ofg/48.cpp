#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
  cJSON *json;
  char *printed_json;
  int prebuffer;
  cJSON_bool format;

  if (size < 1) return 0;

  // Ensure the input is null-terminated
  unsigned char *input = (unsigned char *)malloc(size + 1);
  if (input == NULL) return 0;
  memcpy(input, data, size);
  input[size] = '\0';

  // Parse the input data into a cJSON object
  json = cJSON_Parse((const char *)input);
  free(input);

  if (json == NULL) return 0;

  // Set prebuffer and format values
  prebuffer = 1; // Minimum prebuffer size
  format = (cJSON_bool)(data[0] % 2); // Use the first byte to decide format

  // Call the function-under-test
  printed_json = cJSON_PrintBuffered(json, prebuffer, format);

  // Free the printed JSON string if it was created
  if (printed_json != NULL) {
    free(printed_json);
  }

  // Delete the cJSON object
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif