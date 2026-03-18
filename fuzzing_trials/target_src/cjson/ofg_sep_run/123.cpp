#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  // Split the input data into three parts for creating cJSON items
  size_t part_size = size / 3;
  const uint8_t *data1 = data;
  size_t size1 = part_size;
  const uint8_t *data2 = data + part_size;
  size_t size2 = part_size;
  const uint8_t *data3 = data + 2 * part_size;
  size_t size3 = size - 2 * part_size;

  // Create cJSON items from the data
  cJSON *item1 = cJSON_ParseWithLength((const char *)data1, size1);
  cJSON *item2 = cJSON_ParseWithLength((const char *)data2, size2);
  cJSON *item3 = cJSON_ParseWithLength((const char *)data3, size3);

  if (item1 == NULL || item2 == NULL || item3 == NULL) {
    cJSON_Delete(item1);
    cJSON_Delete(item2);
    cJSON_Delete(item3);
    return 0;
  }

  // Call the function-under-test
  cJSON_ReplaceItemViaPointer(item1, item2, item3);

  // Clean up
  cJSON_Delete(item1);
  cJSON_Delete(item2);
  cJSON_Delete(item3);

  return 0;
}

#ifdef __cplusplus
}
#endif