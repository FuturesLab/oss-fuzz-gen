#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    plist_t original_plist = NULL;
    plist_t copied_plist = NULL;

    // Create a plist from the input data
    if (size > 0) {
        plist_from_bin((const char *)data, size, &original_plist);
    }

    if (original_plist != NULL) {
        // Call the function-under-test
        copied_plist = plist_copy(original_plist);

        // Free the copied plist
        plist_free(copied_plist);

        // Free the original plist
        plist_free(original_plist);
    }

    return 0;
}