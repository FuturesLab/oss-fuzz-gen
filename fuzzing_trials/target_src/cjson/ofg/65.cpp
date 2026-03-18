#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Create a cJSON array
  cJSON *array = cJSON_CreateArray();
  if (array == NULL) {
    return 0;
  }

  // Create a cJSON item to insert
  cJSON *item = cJSON_CreateString("fuzz_item");
  if (item == NULL) {
    cJSON_Delete(array);
    return 0;
  }

  // Use the first byte of data to determine the index
  int index = data[0] % (size + 1); // Ensure index is within bounds

  // Call the function-under-test
  cJSON_bool result = cJSON_InsertItemInArray(array, index, item);

  // Clean up
  cJSON_Delete(array); // This will also delete 'item' if insertion failed

  return 0;
}

#ifdef __cplusplus
}
#endif