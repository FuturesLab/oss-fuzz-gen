extern "C" {
#include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Ensure there is at least one byte to read
    if (size < 1) {
        return 0;
    }

    // Use the first byte of data as the input for plist_new_bool
    uint8_t bool_value = data[0];

    // Call the function-under-test
    plist_t plist = plist_new_bool(bool_value);

    // Clean up the plist object if it was created successfully
    if (plist != NULL) {
        plist_free(plist);
    }

    return 0;
}