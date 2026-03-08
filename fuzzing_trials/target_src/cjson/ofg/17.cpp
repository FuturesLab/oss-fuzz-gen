#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Ensure the input data is null-terminated to be used as a string.
    char *key = (char *)malloc(size + 1);
    if (key == NULL) {
        return 0;
    }
    memcpy(key, data, size);
    key[size] = '\0';

    // Create a root object to add the new object to.
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        free(key);
        return 0;
    }

    // Call the function under test.
    cJSON *new_object = cJSON_AddObjectToObject(root, key);

    // Clean up
    cJSON_Delete(root);
    free(key);

    return 0;
}

#ifdef __cplusplus
}
#endif