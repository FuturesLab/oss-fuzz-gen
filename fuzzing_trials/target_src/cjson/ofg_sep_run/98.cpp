#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Create a root JSON array
    cJSON *root_array = cJSON_CreateArray();
    if (root_array == NULL) {
        return 0;
    }

    // Create a JSON item from the input data
    cJSON *item = cJSON_CreateString((const char *)data);
    if (item == NULL) {
        cJSON_Delete(root_array);
        return 0;
    }

    // Add the item to the array
    cJSON_bool result = cJSON_AddItemToArray(root_array, item);

    // Clean up
    cJSON_Delete(root_array);

    return result;
}

#ifdef __cplusplus
}
#endif