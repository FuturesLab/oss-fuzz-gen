#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Ensure there is enough data for a valid cJSON string and a key
    if (size < 2) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *json_data = (char *)malloc(size + 1);
    if (json_data == NULL) {
        return 0;
    }
    memcpy(json_data, data, size);
    json_data[size] = '\0';

    // Parse the JSON data
    cJSON *json = cJSON_Parse(json_data);
    if (json == NULL) {
        free(json_data);
        return 0;
    }

    // Use the remaining data as a key, ensuring it's null-terminated
    const char *key = (const char *)(data + 1);
    size_t key_length = size - 1;
    char *key_str = (char *)malloc(key_length + 1);
    if (key_str == NULL) {
        cJSON_Delete(json);
        free(json_data);
        return 0;
    }
    memcpy(key_str, key, key_length);
    key_str[key_length] = '\0';

    // Call the function-under-test
    cJSON *item = cJSON_GetObjectItemCaseSensitive(json, key_str);

    // Clean up
    cJSON_Delete(json);
    free(json_data);
    free(key_str);

    return 0;
}

#ifdef __cplusplus
}
#endif