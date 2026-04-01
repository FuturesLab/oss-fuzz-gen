#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Ensure the data is null-terminated for string operations
    char *key = (char *)malloc(size + 1);
    if (!key) {
        return 0;
    }
    memcpy(key, data, size);
    key[size] = '\0';

    // Create a root JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        free(key);
        return 0;
    }

    // Call the function-under-test
    cJSON *array = cJSON_AddArrayToObject(root, key);

    // Clean up
    cJSON_Delete(root);
    free(key);

    return 0;
}

#ifdef __cplusplus
}
#endif