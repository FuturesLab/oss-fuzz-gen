#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    // Initialize plist_t and plist_array_iter
    plist_t plist = NULL;
    plist_array_iter iter;

    // Create a plist node from the input data
    plist_format_t format = PLIST_FORMAT_XML; // Default format
    plist_from_memory((const char*)data, size, &plist, &format);

    // Ensure plist is not NULL
    if (plist != NULL) {
        // Call the function-under-test
        plist_array_new_iter(plist, &iter);

        // Clean up
        plist_free(plist);
    }

    return 0;
}