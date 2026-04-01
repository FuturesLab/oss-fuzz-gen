#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    #include "plist/plist.h"
}

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Initialize plist variables
    plist_t plist = NULL;
    plist_t item = NULL;

    // Check if the size is sufficient to create a plist from memory
    if (size > 0) {
        // Create a plist from the input data
        plist_format_t format;
        plist_from_memory((const char*)data, size, &plist, &format);

        // Ensure the plist is not NULL
        if (plist != NULL) {
            // Assume the plist is an array and get the first item
            item = plist_array_get_item(plist, 0);

            // Call the function-under-test
            uint32_t index = plist_array_get_item_index(item);

            // Print the index for debugging purposes
            printf("Item index: %u\n", index);

            // Free the plist
            plist_free(plist);
        }
    }

    return 0;
}