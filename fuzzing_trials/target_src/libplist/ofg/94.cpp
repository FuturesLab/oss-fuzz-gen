extern "C" {
#include <plist/plist.h>
}

#include <cstring> // Include the necessary C++ header for memcpy

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract a double value
    if (size < sizeof(double)) {
        return 0;
    }

    // Initialize plist
    plist_t plist = plist_new_real(0.0);

    // Extract a double value from the input data
    double value;
    memcpy(&value, data, sizeof(double));

    // Call the function-under-test
    int result = plist_real_val_compare(plist, value);

    // Clean up
    plist_free(plist);

    return 0;
}