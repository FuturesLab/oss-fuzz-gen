#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
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
        plist_free(plist);
    }

    return 0;
}