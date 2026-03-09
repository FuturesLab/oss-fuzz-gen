#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Create a root cJSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        return 0;
    }

    // Use the first part of the data as a key
    size_t key_size = data[0] % (size - 1) + 1; // Ensure key_size is at least 1 and less than size
    char *key = (char *)malloc(key_size + 1);
    if (key == NULL) {
        cJSON_Delete(root);
        return 0;
    }
    memcpy(key, data + 1, key_size);
    key[key_size] = '\0';

    // Use the remaining data to create a cJSON item
    cJSON *item = cJSON_CreateString((const char *)(data + 1 + key_size));
    if (item == NULL) {
        free(key);
        cJSON_Delete(root);
        return 0;
    }

    // Call the function-under-test
    cJSON_bool result = cJSON_AddItemToObjectCS(root, key, item);

    // Clean up
    free(key);
    cJSON_Delete(root);

    return 0;
}

#ifdef __cplusplus
}
#endif