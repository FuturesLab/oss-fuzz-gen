#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    plist_t plist = NULL;

    // Create a plist from the input data
    plist_from_bin((const char *)data, size, &plist);

    // Ensure plist is not NULL before calling the function-under-test
    if (plist != NULL) {
        // Call the function-under-test
        plist_type type = plist_get_node_type(plist);

        // Optionally, you can perform some checks or operations with 'type'
        // For example, print the type (not necessary for fuzzing, but useful for debugging)
        // printf("Node type: %d\n", type);

        // Free the plist to avoid memory leaks
        plist_free(plist);
    }

    return 0;
}