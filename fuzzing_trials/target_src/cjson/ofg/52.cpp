#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  if (!cJSON_IsArray(json)) {
    cJSON_Delete(json);
    return 0;
  }

  int index = 0;
  if (size > sizeof(int)) {
    memcpy(&index, data, sizeof(int));
  }

  cJSON *item = cJSON_GetArrayItem(json, index);
  if (item != NULL) {
    // Access the item to ensure it's not optimized away
    const char *item_string = cJSON_Print(item);
    if (item_string != NULL) {
      free((void *)item_string);
    }
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif