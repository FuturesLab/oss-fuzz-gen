#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy
#include <plist/plist.h>

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract a double value
    if (size < sizeof(double)) {
        return 0;
    }

    // Initialize plist
    plist_t plist = plist_new_real(0.0);

    // Extract a double value from the input data
    double real_value;
    memcpy(&real_value, data, sizeof(double));

    // Call the function-under-test
    plist_set_real_val(plist, real_value);

    // Free the plist
    plist_free(plist);

    return 0;
}