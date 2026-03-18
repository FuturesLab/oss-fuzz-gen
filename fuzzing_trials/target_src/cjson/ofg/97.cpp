#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Create a root JSON array
    cJSON *root_array = cJSON_CreateArray();
    if (root_array == NULL) {
        return 0;
    }

    // Create a new JSON item from the input data
    cJSON *new_item = cJSON_CreateString((const char *)data);
    if (new_item == NULL) {
        cJSON_Delete(root_array);
        return 0;
    }

    // Add the new item to the root array
    cJSON_bool result = cJSON_AddItemToArray(root_array, new_item);

    // Clean up
    cJSON_Delete(root_array); // This will also delete new_item

    return result ? 0 : 1;
}

#ifdef __cplusplus
}
#endif