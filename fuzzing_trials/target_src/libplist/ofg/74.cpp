#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this for memcpy

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an int64_t value
    if (size < sizeof(int64_t)) {
        return 0;
    }

    // Initialize the plist object
    plist_t plist = plist_new_dict();

    // Extract an int64_t value from the input data
    int64_t int_val;
    memcpy(&int_val, data, sizeof(int64_t));

    // Call the function-under-test
    plist_set_int_val(plist, int_val);

    // Clean up the plist object
    plist_free(plist);

    return 0;
}