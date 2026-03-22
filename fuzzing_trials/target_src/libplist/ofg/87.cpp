#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Check if the input data is large enough to be meaningful
    if (size < 1) {
        return 0;
    }

    // Attempt to parse the input data as a plist
    plist_t plist = NULL;
    plist_from_bin((const char*)data, size, &plist);

    // If plist is NULL, the data was not a valid plist
    if (plist == NULL) {
        return 0;
    }

    // Initialize the int64_t variable
    int64_t int_val = 0;

    // Call the function-under-test
    plist_get_int_val(plist, &int_val);

    // Clean up
    plist_free(plist);

    return 0;
}