extern "C" {
#include "plist/plist.h"
}

#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Initialize a plist object
    plist_t plist = plist_new_dict();

    // Ensure the data is not empty
    if (size == 0) {
        plist_free(plist);
        return 0;
    }

    // Create a null-terminated key string from the data
    char *key = new char[size + 1];
    memcpy(key, data, size);
    key[size] = '\0';

    // Add a sample integer value to the plist dictionary
    plist_dict_set_item(plist, key, plist_new_int(42));

    // Call the function-under-test
    int64_t result = plist_dict_get_int(plist, key);

    // Clean up
    plist_free(plist);
    delete[] key;

    return 0;
}