#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    plist_t plist;
    char *string_val = NULL;

    // Create a plist from the input data
    plist_from_bin((const char *)data, (uint32_t)size, &plist);

    if (plist != NULL) {
        // Call the function-under-test
        plist_get_string_val(plist, &string_val);

        // Clean up
        if (string_val != NULL) {
            free(string_val);
        }
        plist_free(plist);
    }

    return 0;
}