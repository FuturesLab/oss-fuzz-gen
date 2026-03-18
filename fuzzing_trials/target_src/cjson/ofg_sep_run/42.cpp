#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
  const char **string_array;
  int array_size;
  cJSON *json_array;
  size_t i, offset = 0;

  // Ensure there's enough data to determine array size
  if (size < sizeof(int)) {
    return 0;
  }

  // Determine the array size from the input data
  array_size = *(int *)data;
  data += sizeof(int);
  size -= sizeof(int);

  // Limit the array size to a reasonable number to prevent excessive memory usage
  if (array_size < 0 || array_size > 100) {
    return 0;
  }

  // Allocate memory for the string array
  string_array = (const char **)malloc(array_size * sizeof(char *));
  if (string_array == NULL) {
    return 0;
  }

  // Populate the string array with non-NULL strings
  for (i = 0; i < (size_t)array_size && offset < size; i++) {
    // Ensure the string is NULL-terminated
    size_t str_len = strnlen((const char *)(data + offset), size - offset);
    if (str_len < size - offset) {
      string_array[i] = (const char *)(data + offset);
      offset += str_len + 1; // Move past the string and its NULL terminator
    } else {
      string_array[i] = "";
    }
  }

  // Create the cJSON string array
  json_array = cJSON_CreateStringArray(string_array, array_size);

  // Free the cJSON object
  if (json_array != NULL) {
    cJSON_Delete(json_array);
  }

  // Free the allocated string array
  free(string_array);

  return 0;
}

#ifdef __cplusplus
}
#endif