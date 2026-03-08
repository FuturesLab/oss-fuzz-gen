#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_133(const uint8_t *data, size_t size) {
  cJSON *json = NULL;
  cJSON *item = NULL;
  char *key = NULL;
  
  // Ensure the input data is null-terminated
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  // Parse the input data as a JSON object
  json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  // Allocate memory for the key
  key = (char *)malloc(size);
  if (key == NULL) {
    cJSON_Delete(json);
    return 0;
  }

  // Copy the data to the key, ensuring it's null-terminated
  strncpy(key, (const char *)data, size - 1);
  key[size - 1] = '\0';

  // Call the function-under-test
  item = cJSON_GetObjectItem(json, key);

  // Clean up
  free(key);
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif