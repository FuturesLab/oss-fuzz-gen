#include <stdint.h>
#include <stddef.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Initialize a uint8_t variable to pass to plist_new_bool
    uint8_t bool_value;

    // Check if the size is at least 1 to safely read a byte from data
    if (size > 0) {
        bool_value = data[0];
    } else {
        // If size is 0, set a default value
        bool_value = 1; // true
    }

    // Call the function under test
    plist_t result = plist_new_bool(bool_value);

    // Clean up the plist object if it was created
    if (result != NULL) {
        plist_free(result);
    }

    return 0;
}