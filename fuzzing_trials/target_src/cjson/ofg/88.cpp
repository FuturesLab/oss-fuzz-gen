#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Ensure the data is null-terminated to be used as a string.
    char *json_string = (char *)malloc(size + 1);
    if (!json_string) {
        return 0;
    }
    memcpy(json_string, data, size);
    json_string[size] = '\0';

    // Parse the input data as a JSON object.
    cJSON *json = cJSON_Parse(json_string);
    free(json_string);

    if (json == NULL) {
        return 0;
    }

    // Use a portion of the data as the key for cJSON_GetObjectItemCaseSensitive.
    size_t key_size = size / 2;
    char *key = (char *)malloc(key_size + 1);
    if (!key) {
        cJSON_Delete(json);
        return 0;
    }
    memcpy(key, data + (size - key_size), key_size);
    key[key_size] = '\0';

    // Call the function-under-test.
    cJSON *item = cJSON_GetObjectItemCaseSensitive(json, key);

    // Clean up.
    free(key);
    cJSON_Delete(json);

    return 0;
}

#ifdef __cplusplus
}
#endif