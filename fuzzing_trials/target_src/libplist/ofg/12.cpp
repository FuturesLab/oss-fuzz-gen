extern "C" {
#include "/src/libplist/libcnary/include/node.h"
#include "/src/libplist/include/plist/plist.h"
}

#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    plist_t plist;
    char key[256]; // Assuming a reasonable size for the key

    // Initialize plist
    plist = plist_new_dict();

    // Ensure the size is sufficient for a key
    if (size < 1) {
        plist_free(plist);
        return 0;
    }

    // Copy data into key ensuring null-termination
    size_t key_len = size < sizeof(key) ? size : sizeof(key) - 1;
    memcpy(key, data, key_len);
    key[key_len] = '\0';

    // Add a key-value pair to plist for testing
    plist_dict_set_item(plist, "test_key", plist_new_string("test_value"));

    // Call the function-under-test
    int result = plist_key_val_contains(plist, key);

    // Clean up
    plist_free(plist);

    return 0;
}