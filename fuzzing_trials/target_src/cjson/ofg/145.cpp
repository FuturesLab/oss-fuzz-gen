#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    if (size < 2) return 0;

    // Create a root JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) return 0;

    // Create a referenced JSON item
    cJSON *item = cJSON_CreateString("example");
    if (item == NULL) {
        cJSON_Delete(root);
        return 0;
    }

    // Ensure the key is null-terminated
    char key[256];
    size_t key_length = size < 255 ? size : 255;
    memcpy(key, data, key_length);
    key[key_length] = '\0';

    // Call the function-under-test
    cJSON_bool result = cJSON_AddItemReferenceToObject(root, key, item);

    // Clean up
    cJSON_Delete(root);
    // Note: item is not deleted because it is referenced by root

    return 0;
}

#ifdef __cplusplus
}
#endif