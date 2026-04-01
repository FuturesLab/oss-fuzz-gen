#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    if (size < 3) return 0; // Ensure there's enough data for non-empty strings

    // Split the input data into three parts for object, key, and value
    size_t part_size = size / 3;
    const char *object_data = (const char *)data;
    const char *key_data = (const char *)(data + part_size);
    const char *value_data = (const char *)(data + 2 * part_size);

    // Ensure the strings are null-terminated
    char *object_str = (char *)malloc(part_size + 1);
    char *key_str = (char *)malloc(part_size + 1);
    char *value_str = (char *)malloc(part_size + 1);

    if (!object_str || !key_str || !value_str) {
        free(object_str);
        free(key_str);
        free(value_str);
        return 0;
    }

    memcpy(object_str, object_data, part_size);
    object_str[part_size] = '\0';
    memcpy(key_str, key_data, part_size);
    key_str[part_size] = '\0';
    memcpy(value_str, value_data, part_size);
    value_str[part_size] = '\0';

    // Create a cJSON object
    cJSON *json_object = cJSON_Parse(object_str);
    if (json_object == NULL) {
        json_object = cJSON_CreateObject();
    }

    // Call the function-under-test
    cJSON *result = cJSON_AddStringToObject(json_object, key_str, value_str);

    // Clean up
    cJSON_Delete(json_object);
    free(object_str);
    free(key_str);
    free(value_str);

    return 0;
}

#ifdef __cplusplus
}
#endif