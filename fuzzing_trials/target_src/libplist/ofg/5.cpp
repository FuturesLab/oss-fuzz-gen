#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include the string.h library for memcpy

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Ensure the size is at least 8 bytes to read an int64_t
    if (size < sizeof(int64_t)) {
        return 0;
    }

    // Read the first 8 bytes of data as an int64_t
    int64_t value;
    memcpy(&value, data, sizeof(int64_t));

    // Call the function-under-test
    plist_t plist = plist_new_int(value);

    // Clean up the plist object if it was created
    if (plist != NULL) {
        plist_free(plist);
    }

    return 0;
}