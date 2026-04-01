#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    // Initialize plist_t variable
    plist_t plist = plist_new_dict();

    // Ensure data is not empty
    if (size >= sizeof(int64_t)) {
        // Extract an int64_t value from the data
        int64_t value;
        memcpy(&value, data, sizeof(int64_t));

        // Call the function-under-test
        int result = plist_int_val_compare(plist, value);

        // Output the result (optional, for debugging purposes)
        printf("Comparison result: %d\n", result);
    }

    // Free the plist object
    plist_free(plist);

    return 0;
}