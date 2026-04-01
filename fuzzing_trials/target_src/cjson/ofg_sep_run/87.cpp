#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Ensure null-termination for the key string
    char *key = (char *)malloc(size);
    if (key == NULL) {
        return 0;
    }
    memcpy(key, data, size - 1);
    key[size - 1] = '\0';

    // Parse the JSON data
    cJSON *json = cJSON_Parse((const char *)data);
    if (json == NULL) {
        free(key);
        return 0;
    }

    // Call the function under test
    cJSON *item = cJSON_GetObjectItemCaseSensitive(json, key);

    // Clean up
    cJSON_Delete(json);
    free(key);

    return 0;
}

#ifdef __cplusplus
}
#endif