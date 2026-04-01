#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    // Initialize a plist variable
    plist_t node = NULL;

    // Create a plist node from the input data
    if (size > 0) {
        plist_from_bin((const char *)data, size, &node);
    }

    // Ensure node is not NULL
    if (node != NULL) {
        // Call the function-under-test
        plist_t parent = plist_get_parent(node);

        // Clean up
        plist_free(parent);
        plist_free(node);
    }

    return 0;
}