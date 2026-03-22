#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a plist from the input data
    plist_t plist = NULL;
    plist_from_bin((const char*)data, size, &plist);

    if (plist != NULL) {
        // Call the function-under-test
        plist_type type = plist_get_node_type(plist);

        // Optionally, handle the type or perform additional operations
        // For example, printing the type (not required for fuzzing)
        // printf("Node type: %d\n", type);

        // Free the plist
        plist_free(plist);
    }

    return 0;
}