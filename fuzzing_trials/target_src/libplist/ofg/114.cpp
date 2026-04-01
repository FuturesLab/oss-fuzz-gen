#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy
#include <plist/plist.h>

extern "C" {
    // Include necessary C headers and functions here
}

extern "C" int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    // Ensure that we have enough data to interpret as a double
    if (size < sizeof(double)) {
        return 0;
    }

    // Interpret the first sizeof(double) bytes of data as a double
    double real_value;
    memcpy(&real_value, data, sizeof(double));

    // Call the function-under-test
    plist_t plist = plist_new_real(real_value);

    // Clean up the plist object if it was created successfully
    if (plist != NULL) {
        plist_free(plist);
    }

    return 0;
}