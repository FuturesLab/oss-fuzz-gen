#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Ensure the string is null-terminated
    char *key = (char *)malloc(size + 1);
    if (!key) {
        return 0;
    }
    memcpy(key, data, size);
    key[size] = '\0';

    // Create a new JSON object
    cJSON *json = cJSON_CreateObject();
    if (json == NULL) {
        free(key);
        return 0;
    }

    // Call the function-under-test
    cJSON *result = cJSON_AddTrueToObject(json, key);

    // Clean up
    cJSON_Delete(json);
    free(key);

    return 0;
}

#ifdef __cplusplus
}
#endif