#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "plist/plist.h"
}

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Create a plist from the input data
    plist_t plist = NULL;
    if (size > 0) {
        plist_format_t format = PLIST_FORMAT_XML; // or any default format you prefer
        plist_from_memory((const char*)data, size, &plist, &format);
    }

    // Ensure plist is not NULL
    if (plist != NULL) {
        // Call the function-under-test
        uint32_t array_size = plist_array_get_size(plist);

        // Optional: Use the result to prevent compiler optimizations
        (void)array_size;

        // Free the plist

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_array_get_size to plist_data_val_compare
        plist_t ret_plist_get_parent_ekeyw = plist_get_parent(0);
        const uint8_t dgjkozsq = -1;

        int ret_plist_data_val_compare_eyavp = plist_data_val_compare(ret_plist_get_parent_ekeyw, &dgjkozsq, (size_t )array_size);
        if (ret_plist_data_val_compare_eyavp < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        plist_free(plist);
    }

    return 0;
}