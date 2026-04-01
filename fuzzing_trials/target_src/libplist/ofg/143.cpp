#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    // Initialize plist_t and uint64_t pointer
    plist_t plist = NULL;
    uint64_t uint_val = 0;

    // Create a plist from the input data
    plist_from_bin((const char *)data, size, &plist);

    // Ensure plist is not NULL
    if (plist != NULL) {
        // Call the function-under-test
        plist_get_uint_val(plist, &uint_val);

        // Free the plist to prevent memory leaks
        plist_free(plist);
    }

    return 0;
}