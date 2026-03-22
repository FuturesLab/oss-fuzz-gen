#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    // Initialize plist_t variables
    plist_t array = plist_new_array();
    plist_t item = nullptr;

    // Ensure that the input data is not null and has a valid size
    if (data && size > 0) {
        item = plist_new_data((const char*)data, size);
    }

    // Ensure that neither array nor item is NULL
    if (array && item) {
        // Call the function-under-test
        plist_array_append_item(array, item);

        // Clean up: Since plist_array_append_item transfers ownership of item to array,
        // we only need to free the array
        plist_free(array);
    } else {
        // Clean up in case of failure to create plist_t objects
        if (array) plist_free(array);
        if (item) plist_free(item);
    }

    return 0;
}