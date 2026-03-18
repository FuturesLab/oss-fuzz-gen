#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a cJSON object
    cJSON *object = cJSON_CreateObject();
    if (object == NULL) {
        return 0;
    }

    // Ensure the string is null-terminated
    char *key = (char *)malloc(size + 1);
    if (key == NULL) {
        cJSON_Delete(object);
        return 0;
    }
    memcpy(key, data, size);
    key[size] = '\0';

    // Call the function-under-test
    cJSON *result = cJSON_AddTrueToObject(object, key);

    // Clean up
    free(key);
    cJSON_Delete(object);

    return 0;
}

#ifdef __cplusplus
}
#endif