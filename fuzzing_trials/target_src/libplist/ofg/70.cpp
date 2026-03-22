#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize plist_t object
    plist_t plist = plist_new_data((const char*)data, (uint32_t)size);

    // Initialize a uint64_t variable
    uint64_t length = 0;

    // Call the function-under-test
    const char *result = plist_get_data_ptr(plist, &length);

    // Check if result is not null and length is greater than 0
    if (result && length > 0) {
        // Do something with result to ensure code coverage
        volatile char first_char = result[0];
        (void)first_char; // Prevent unused variable warning
    }

    // Cleanup
    plist_free(plist);

    return 0;
}