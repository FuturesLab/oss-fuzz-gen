#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Ensure the data is null-terminated for safe string operations
    char *key = (char *)malloc(size + 1);
    if (key == NULL) {
        return 0;
    }
    memcpy(key, data, size);
    key[size] = '\0';

    // Create a simple JSON object for testing
    cJSON *json = cJSON_CreateObject();
    if (json == NULL) {
        free(key);
        return 0;
    }

    // Add some items to the JSON object
    cJSON_AddStringToObject(json, "example_key", "example_value");
    cJSON_AddNumberToObject(json, "number_key", 42);

    // Call the function-under-test
    cJSON_DeleteItemFromObjectCaseSensitive(json, key);

    // Clean up
    cJSON_Delete(json);
    free(key);

    return 0;
}

#ifdef __cplusplus
}
#endif