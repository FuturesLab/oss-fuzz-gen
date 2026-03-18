#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Create a root JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        return 0;
    }

    // Create a new JSON item
    cJSON *item = cJSON_CreateString("value");
    if (item == NULL) {
        cJSON_Delete(root);
        return 0;
    }

    // Use the first byte of data as the length of the key
    size_t key_length = data[0] % (size - 1) + 1;
    char *key = (char *)malloc(key_length + 1);
    if (key == NULL) {
        cJSON_Delete(root);
        cJSON_Delete(item);
        return 0;
    }

    // Copy the key from the data
    memcpy(key, data + 1, key_length);
    key[key_length] = '\0';

    // Add the item to the JSON object
    cJSON_bool result = cJSON_AddItemToObject(root, key, item);

    // Clean up
    free(key);
    cJSON_Delete(root);

    return 0;
}

#ifdef __cplusplus
}
#endif