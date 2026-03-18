#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  char *string_value = cJSON_GetStringValue(json);

  /* Use the string_value for fuzzing purposes, if needed */
  if (string_value != NULL) {
    /* For example, we could print it, but in fuzzing, we usually avoid output */
    /* printf("String value: %s\n", string_value); */
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif