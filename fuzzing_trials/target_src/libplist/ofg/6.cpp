#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" {
    // Include necessary C headers and functions
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize a plist variable
    plist_t plist = NULL;

    // Create a plist node from the input data
    // Convert data to const char* as required by plist_from_bin
    plist_from_bin(reinterpret_cast<const char*>(data), static_cast<uint32_t>(size), &plist);

    if (plist != NULL) {
        // Call the function-under-test
        int result = plist_bool_val_is_true(plist);

        // Clean up
        plist_free(plist);
    }

    return 0;
}