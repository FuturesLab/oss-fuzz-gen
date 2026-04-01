#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include the string.h library for memcpy
#include <plist/plist.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
}

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    if (size < sizeof(int64_t)) {
        return 0; // Not enough data to form an int64_t
    }

    int64_t int_value;
    // Copy the first 8 bytes from data to int_value
    memcpy(&int_value, data, sizeof(int64_t));

    // Call the function-under-test
    plist_t plist = plist_new_int(int_value);

    // Clean up plist object if necessary
    if (plist != NULL) {
        plist_free(plist);
    }

    return 0;
}