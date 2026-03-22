#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include the necessary header for memcpy

extern "C" {
    #include "plist/plist.h"

    int plist_real_val_compare(plist_t plist, double value);
}

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    // Initialize plist
    plist_t plist = plist_new_real(0.0); // Create a new plist with a real value

    // Ensure we have at least 8 bytes to read a double value
    if (size < sizeof(double)) {
        plist_free(plist);
        return 0;
    }

    // Read a double value from the input data
    double real_value;
    memcpy(&real_value, data, sizeof(double));

    // Call the function-under-test
    int result = plist_real_val_compare(plist, real_value);

    // Free the plist
    plist_free(plist);

    return 0;
}