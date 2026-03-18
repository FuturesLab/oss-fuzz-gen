#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
  if (size < 1) return 0;

  // Create a JSON object
  cJSON *json = cJSON_CreateObject();
  if (json == NULL) return 0;

  // Use the first byte of data as part of the key
  char key[2] = { (char)data[0], '\0' };

  // Use the remaining data to create a double value
  double number = 0.0;
  if (size >= sizeof(double) + 1) {
    memcpy(&number, data + 1, sizeof(double));
  }

  // Call the function under test
  cJSON *result = cJSON_AddNumberToObject(json, key, number);

  // Clean up
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif