#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
  if (size < 2) return 0; // Ensure there is enough data to proceed

  // Create a new cJSON array
  cJSON *array = cJSON_CreateArray();
  if (array == NULL) {
    return 0;
  }

  // Create a new cJSON item
  cJSON *item = cJSON_CreateString("fuzz_item");
  if (item == NULL) {
    cJSON_Delete(array);
    return 0;
  }

  // Use the first byte of data to determine the index
  int index = (int)(data[0] % 10); // Limit index to a reasonable size

  // Call the function-under-test
  cJSON_InsertItemInArray(array, index, item);

  // Clean up
  cJSON_Delete(array); // This will also delete the item if it was inserted

  return 0;
}

#ifdef __cplusplus
}
#endif