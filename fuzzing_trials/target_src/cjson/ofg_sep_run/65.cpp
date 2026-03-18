#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

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

    // Determine the index to insert the item at
    int index = data[0] % (size + 1); // Ensure index is within bounds

    // Call the function-under-test
    cJSON_bool result = cJSON_InsertItemInArray(array, index, item);

    // Clean up
    cJSON_Delete(array);
    // Note: No need to delete 'item' as it is managed by the array now

    return 0;
}

#ifdef __cplusplus
}
#endif