#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a plist
    if (size < 1) {
        return 0;
    }

    // Create a plist from the input data
    plist_t plist = plist_new_data((const char *)data, (uint32_t)size);

    // Initialize the iterator
    plist_dict_iter iter;

    // Call the function-under-test
    plist_dict_new_iter(plist, &iter);

    // Clean up
    plist_free(plist);

    return 0;
}