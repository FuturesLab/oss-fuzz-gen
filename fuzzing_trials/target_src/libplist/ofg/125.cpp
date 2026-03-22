#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    // Initialize the plist_t variable
    plist_t plist = NULL;

    // Create a plist from the input data
    plist_from_bin((const char*)data, size, &plist);

    // If the plist is not NULL, call the function-under-test
    if (plist != NULL) {
        // Call the function-under-test
        uint32_t index = plist_array_get_item_index(plist);

        // Optionally, perform some operations with the index
        (void)index; // Suppress unused variable warning
    }

    // Free the plist
    plist_free(plist);

    return 0;
}