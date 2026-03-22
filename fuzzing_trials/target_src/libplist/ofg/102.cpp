#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for creating a plist object
    if (size < 1) {
        return 0;
    }

    // Create a plist object from the input data
    plist_t plist = NULL;
    plist_from_bin((const char *)data, size, &plist);

    if (!plist) {
        return 0;
    }

    // Initialize a uint8_t variable to store the boolean value
    uint8_t bool_val = 0;

    // Call the function-under-test
    plist_get_bool_val(plist, &bool_val);

    // Free the plist object
    plist_free(plist);

    return 0;
}