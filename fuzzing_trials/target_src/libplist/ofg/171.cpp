#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_171(const uint8_t *data, size_t size) {
    // Initialize plist variables
    plist_t plist = NULL;
    plist_t key = NULL;

    // Create a plist from fuzz data
    if (size > 0) {
        plist_from_bin((const char *)data, size, &plist);
    }

    // Ensure the plist is not NULL
    if (plist != NULL) {
        // Call the function-under-test
        key = plist_dict_item_get_key(plist);

        // Free the key if it was allocated
        if (key != NULL) {
            plist_free(key);
        }

        // Free the plist
        plist_free(plist);
    }

    return 0;
}