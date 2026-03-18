#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
  cJSON *json;
  char *key;
  size_t offset = 1;

  if (size <= offset)
    return 0;
  if (data[size - 1] != '\0')
    return 0;

  json = cJSON_Parse((const char *)data);

  if (json == NULL)
    return 0;

  key = (char *)malloc(size - offset + 1);
  if (key == NULL) {
    cJSON_Delete(json);
    return 0;
  }

  memcpy(key, data + offset, size - offset);
  key[size - offset] = '\0';

  cJSON_bool result = cJSON_HasObjectItem(json, key);

  free(key);
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif