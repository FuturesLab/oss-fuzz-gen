extern "C" {
#include <plist/plist.h>
}

#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Initialize plist variables
    plist_t plist = nullptr;
    plist_array_iter iter = nullptr;
    plist_t next_item = nullptr;

    // Create a plist from the input data
    plist_from_bin((const char*)data, size, &plist);

    // Create an iterator for the plist array
    plist_array_new_iter(plist, &iter);

    // Call the function-under-test
    plist_array_next_item(plist, iter, &next_item);

    // Clean up
    if (next_item) {
        plist_free(next_item);
    }
    if (iter) {
        free(iter);
    }
    if (plist) {
        plist_free(plist);
    }

    return 0;
}