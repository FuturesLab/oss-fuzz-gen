#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
  cJSON *json;
  cJSON *item;
  char *key;
  size_t offset = 4;

  if (size <= offset)
    return 0;
  if (data[size - 1] != '\0')
    return 0;

  json = cJSON_ParseWithOpts((const char *)data + offset, NULL, 1);
  if (json == NULL)
    return 0;

  key = (char *)malloc(size);
  if (key == NULL) {
    cJSON_Delete(json);
    return 0;
  }

  memcpy(key, data, size);
  key[size - 1] = '\0';

  item = cJSON_GetObjectItem(json, key);

  /* Use item here if needed, but for fuzzing, we just need to call the function */

  free(key);
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif