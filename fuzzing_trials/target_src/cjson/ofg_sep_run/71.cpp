#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Split the input data for index and JSON strings
    int index = data[0] % 10;  // Limit index to a small number for simplicity
    const char *json_string = (const char *)(data + 1);

    // Parse the JSON string to create a cJSON array
    cJSON *json_array = cJSON_Parse(json_string);
    if (json_array == NULL) {
        return 0;
    }

    // Ensure it's an array
    if (!cJSON_IsArray(json_array)) {
        cJSON_Delete(json_array);
        return 0;
    }

    // Create a new item to replace an existing one in the array
    cJSON *new_item = cJSON_CreateString("new_item");
    if (new_item == NULL) {
        cJSON_Delete(json_array);
        return 0;
    }

    // Call the function-under-test
    cJSON_ReplaceItemInArray(json_array, index, new_item);

    // Clean up
    cJSON_Delete(json_array);

    return 0;
}

#ifdef __cplusplus
}
#endif