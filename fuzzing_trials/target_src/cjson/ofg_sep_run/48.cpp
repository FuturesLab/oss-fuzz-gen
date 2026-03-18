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
  char *printed_json = NULL;
  int prebuffer;
  cJSON_bool formatted;

  if (size < 1) return 0;

  // Ensure the input data is null-terminated for parsing
  unsigned char *input_data = (unsigned char *)malloc(size + 1);
  if (input_data == NULL) return 0;
  memcpy(input_data, data, size);
  input_data[size] = '\0';

  // Parse the JSON data
  json = cJSON_Parse((const char *)input_data);
  free(input_data);

  if (json == NULL) return 0;

  // Use the first byte of the input data to determine prebuffer size
  prebuffer = data[0] % 256; // Ensure prebuffer is within a reasonable range

  // Use the second byte of the input data to determine if the output should be formatted
  formatted = (size > 1 && data[1] % 2 == 0) ? 1 : 0;

  // Call the function-under-test
  printed_json = cJSON_PrintBuffered(json, prebuffer, formatted);

  // Free the printed JSON string if it was created
  if (printed_json != NULL) {
    free(printed_json);
  }

  // Delete the parsed JSON object
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif