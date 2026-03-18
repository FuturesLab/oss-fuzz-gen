#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts
    size_t key_size = data[0] % size;
    size_t value_size = size - key_size - 1;

    // Ensure null-terminated strings
    char *key = (char *)malloc(key_size + 1);
    char *value = (char *)malloc(value_size + 1);
    if (!key || !value) {
        free(key);
        free(value);
        return 0;
    }

    memcpy(key, data + 1, key_size);
    key[key_size] = '\0';

    memcpy(value, data + 1 + key_size, value_size);
    value[value_size] = '\0';

    // Create a cJSON object and item
    cJSON *json_object = cJSON_CreateObject();
    cJSON *new_item = cJSON_CreateString(value);

    if (json_object && new_item) {
        // Call the function under test
        cJSON_ReplaceItemInObject(json_object, key, new_item);
    }

    // Clean up
    cJSON_Delete(json_object); // This will also delete new_item if it was added to the object
    free(key);
    free(value);

    return 0;
}

#ifdef __cplusplus
}
#endif