#include <stdint.h>
#include <stdlib.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Call the function-under-test
    cJSON *json_array = cJSON_CreateArray();

    // Perform operations on the created array to ensure it is used
    if (json_array != NULL) {
        // Add some elements to the array to test its functionality
        cJSON_AddItemToArray(json_array, cJSON_CreateNumber(42));
        cJSON_AddItemToArray(json_array, cJSON_CreateString("fuzz"));

        // Clean up by deleting the created cJSON array
        cJSON_Delete(json_array);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif