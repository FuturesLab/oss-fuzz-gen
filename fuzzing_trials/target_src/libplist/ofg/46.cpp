#include <stdint.h>
#include <stddef.h>
#include <plist/plist.h>
#include <stdlib.h> // Include the standard library for free

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a plist
    if (size < 1) {
        return 0;
    }

    // Create a plist from the input data
    plist_t plist = NULL;
    plist_from_bin((const char*)data, size, &plist);

    if (plist == NULL) {
        return 0;
    }

    // Create an iterator for the plist array
    plist_array_iter iter = NULL;
    plist_array_new_iter(plist, &iter);

    if (iter == NULL) {
        plist_free(plist);
        return 0;
    }

    // Prepare a variable to hold the next item
    plist_t next_item = NULL;

    // Call the function-under-test
    plist_array_next_item(plist, iter, &next_item);

    // Clean up
    if (next_item != NULL) {
        plist_free(next_item);
    }
    free(iter);
    plist_free(plist);

    return 0;
}