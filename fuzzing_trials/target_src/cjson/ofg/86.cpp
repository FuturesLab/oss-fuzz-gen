#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a cJSON object
    cJSON *json_object = cJSON_CreateObject();
    if (json_object == NULL) {
        return 0;
    }

    // Ensure the string is null-terminated
    char *key = (char *)malloc(size + 1);
    if (key == NULL) {
        cJSON_Delete(json_object);
        return 0;
    }
    memcpy(key, data, size);
    key[size] = '\0';

    // Call the function-under-test
    cJSON *array = cJSON_AddArrayToObject(json_object, key);

    // Clean up
    free(key);
    cJSON_Delete(json_object);

    return 0;
}

#ifdef __cplusplus
}
#endif