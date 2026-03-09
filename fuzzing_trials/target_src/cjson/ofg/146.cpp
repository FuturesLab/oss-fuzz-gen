#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Create a root object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        return 0;
    }

    // Create an item to reference
    cJSON *item = cJSON_CreateString("sample_item");
    if (item == NULL) {
        cJSON_Delete(root);
        return 0;
    }

    // Use the first byte of data as the length of the key
    size_t key_length = data[0] % (size - 1) + 1; // Ensure at least 1 character
    char *key = (char *)malloc(key_length + 1);
    if (key == NULL) {
        cJSON_Delete(root);
        cJSON_Delete(item);
        return 0;
    }

    // Copy the key from data
    memcpy(key, data + 1, key_length);
    key[key_length] = '\0';

    // Call the function under test
    cJSON_bool result = cJSON_AddItemReferenceToObject(root, key, item);

    // Clean up
    free(key);
    cJSON_Delete(root); // This also deletes the item

    return 0;
}

#ifdef __cplusplus
}
#endif