#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "/src/cjson/cJSON.h"

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Determine the number of strings to create
  int num_strings = data[0] % 10 + 1; // Ensure at least one string and at most 10

  // Allocate memory for the array of strings
  const char **string_array = (const char **)malloc(num_strings * sizeof(char *));
  if (string_array == NULL) {
    return 0;
  }

  size_t offset = 1;
  for (int i = 0; i < num_strings; i++) {
    if (offset >= size) {
      string_array[i] = "";
    } else {
      size_t string_length = data[offset] % (size - offset) + 1;
      string_array[i] = (const char *)(data + offset);
      offset += string_length;
    }
  }

  // Call the function-under-test
  cJSON *json_array = cJSON_CreateStringArray(string_array, num_strings);

  // Clean up
  cJSON_Delete(json_array);
  free(string_array);

  return 0;
}

#ifdef __cplusplus
}
#endif