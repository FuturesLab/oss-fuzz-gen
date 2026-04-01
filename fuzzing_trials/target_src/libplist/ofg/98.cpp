#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    plist_t plist = NULL;
    uint32_t index = 0;
    void *dummy_ptr = (void*)0x1; // Non-NULL dummy pointer

    // Initialize a plist from the input data
    if (size > 0) {
        plist_from_bin((const char*)data, size, &plist);
    }

    // Call the function-under-test
    plist_t result = plist_access_path(plist, index, dummy_ptr);

    // Clean up
    if (plist != NULL) {
        plist_free(plist);
    }

    return 0;
}