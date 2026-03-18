#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_133(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Ensure the data is null-terminated for string operations
    char *json_data = (char *)malloc(size + 1);
    if (json_data == NULL) {
        return 0;
    }
    memcpy(json_data, data, size);
    json_data[size] = '\0';

    // Parse the input JSON data
    cJSON *json = cJSON_Parse(json_data);
    free(json_data);

    if (json == NULL) {
        return 0;
    }

    // Use a fixed key for testing
    const char *key = "test_key";

    // Call the function-under-test
    cJSON *item = cJSON_GetObjectItem(json, key);

    // Clean up
    cJSON_Delete(json);

    return 0;
}

#ifdef __cplusplus
}
#endif