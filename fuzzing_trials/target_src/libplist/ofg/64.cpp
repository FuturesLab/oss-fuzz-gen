extern "C" {
#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    plist_t plist = NULL;
    uint64_t uint_val = 0;

    // Ensure we have enough data to extract a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Initialize plist
    plist = plist_new_dict();
    if (!plist) {
        return 0;
    }

    // Extract a uint64_t value from the input data
    uint_val = *(reinterpret_cast<const uint64_t *>(data));

    // Call the function-under-test
    plist_set_uint_val(plist, uint_val);

    // Free the plist object
    plist_free(plist);

    return 0;
}