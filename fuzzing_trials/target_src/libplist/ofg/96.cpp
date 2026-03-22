#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Create a plist from the input data
    plist_t plist = NULL;
    plist_from_bin((const char*)data, size, &plist);

    // Check if the plist is not NULL and is a dictionary
    if (plist && plist_get_node_type(plist) == PLIST_DICT) {
        // Call the function-under-test
        uint32_t dict_size = plist_dict_get_size(plist);
    }

    // Free the plist
    if (plist) {
        plist_free(plist);
    }

    return 0;
}