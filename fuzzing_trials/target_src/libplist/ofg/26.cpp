#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Ensure the size is at least 8 bytes to read a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Read the first 8 bytes of data as a uint64_t
    uint64_t value = *(const uint64_t *)data;

    // Call the function-under-test
    plist_t plist = plist_new_uint(value);

    // Clean up the plist object if needed
    if (plist != NULL) {
        plist_free(plist);
    }

    return 0;
}