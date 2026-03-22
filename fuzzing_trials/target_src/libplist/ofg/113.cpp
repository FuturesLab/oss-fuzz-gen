#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>
#include <cstring>

extern "C" {
    // Include necessary C headers
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a double value
    if (size < sizeof(double)) {
        return 0;
    }

    // Extract a double value from the input data
    double real_value;
    memcpy(&real_value, data, sizeof(double));

    // Call the function-under-test
    plist_t plist = plist_new_real(real_value);

    // Clean up the plist object
    if (plist != NULL) {
        plist_free(plist);
    }

    return 0;
}