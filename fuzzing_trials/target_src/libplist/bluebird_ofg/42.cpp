#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libplist/libcnary/include/node.h"
    #include "plist/plist.h"

    int plist_key_val_contains(plist_t, const char *);
}

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Create a plist_t object
    plist_t plist = plist_new_dict();

    // Ensure there is enough data to create a key
    if (size < 1) {
        plist_free(plist);
        return 0;
    }

    // Use the first byte to determine the length of the key (to ensure it's not too long)
    size_t key_length = data[0] % (size - 1) + 1; // Ensure at least 1 byte for the key
    if (key_length > size - 1) {
        key_length = size - 1;
    }

    // Allocate memory for the key and copy data into it
    char *key = (char *)malloc(key_length + 1);
    if (key == NULL) {
        plist_free(plist);
        return 0;
    }
    memcpy(key, data + 1, key_length);
    key[key_length] = '\0'; // Null-terminate the key

    // Add a dummy key-value pair to the plist
    plist_dict_set_item(plist, key, plist_new_string("dummy_value"));

    // Call the function-under-test
    plist_key_val_contains(plist, key);

    // Clean up
    free(key);
    plist_free(plist);

    return 0;
}