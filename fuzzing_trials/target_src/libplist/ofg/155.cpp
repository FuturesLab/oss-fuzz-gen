#include <stdint.h>
#include <stddef.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    plist_t node = NULL;
    plist_t parent = NULL;

    // Create a plist node from the input data
    plist_from_bin((const char*)data, size, &node);

    if (node != NULL) {
        // Call the function-under-test
        parent = plist_get_parent(node);

        // Clean up
        plist_free(node);
    }

    return 0;
}