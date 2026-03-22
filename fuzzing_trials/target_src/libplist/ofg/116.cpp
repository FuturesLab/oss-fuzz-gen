#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" {
    int plist_int_val_is_negative(plist_t node);
}

extern "C" int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    if (size < sizeof(int64_t)) {
        return 0;
    }

    // Initialize plist
    plist_t node = plist_new_int(0);

    // Copy data to an int64_t variable
    int64_t value;
    memcpy(&value, data, sizeof(int64_t));

    // Set the integer value in the plist node
    plist_set_int_val(node, value);

    // Call the function-under-test
    int result = plist_int_val_is_negative(node);

    // Clean up
    plist_free(node);

    return 0;
}