#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "/src/libplist/include/plist/plist.h"
}

extern "C" int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size) {
    if (size < 2) { // Ensure there's enough data for at least a key and a value
        return 0;
    }

    // Create a plist node
    plist_t plist = plist_new_dict();
    if (!plist) {
        return 0;
    }

    // Split the input data into two parts: key and value
    size_t key_size = size / 2;
    size_t value_size = size - key_size;

    // Ensure the key and value are null-terminated
    char *key = (char *)malloc(key_size + 1);
    char *value = (char *)malloc(value_size + 1);
    if (!key || !value) {
        plist_free(plist);
        free(key);
        free(value);
        return 0;
    }
    memcpy(key, data, key_size);
    key[key_size] = '\0';
    memcpy(value, data + key_size, value_size);
    value[value_size] = '\0';

    // Create a plist string node for the value
    plist_t value_node = plist_new_string(value);

    // Call the function-under-test
    plist_dict_set_item(plist, key, value_node);

    // Clean up
    free(key);
    free(value);
    plist_free(plist);

    return 0;
}