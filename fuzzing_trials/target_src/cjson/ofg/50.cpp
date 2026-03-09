#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 2) return 0;

    // Split the input data into two parts
    size_t half_size = size / 2;
    size_t remaining_size = size - half_size;

    // Create a null-terminated string for the key
    char *key = (char *)malloc(half_size + 1);
    if (key == NULL) return 0;
    memcpy(key, data, half_size);
    key[half_size] = '\0';

    // Parse the remaining data as a JSON object
    cJSON *json_object = cJSON_ParseWithLength((const char *)(data + half_size), remaining_size);
    if (json_object == NULL) {
        free(key);
        return 0;
    }

    // Create a new cJSON item to add
    cJSON *new_item = cJSON_CreateString("fuzzed_item");
    if (new_item == NULL) {
        cJSON_Delete(json_object);
        free(key);
        return 0;
    }

    // Call the function-under-test
    cJSON_bool result = cJSON_AddItemToObjectCS(json_object, key, new_item);

    // Clean up
    cJSON_Delete(json_object);
    free(key);

    return 0;
}

#ifdef __cplusplus
}
#endif