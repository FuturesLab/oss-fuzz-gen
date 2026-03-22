#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    // Initialize plist_t and uint64_t* variables
    plist_t plist = NULL;
    uint64_t length = 0;

    // Create a plist from the input data
    plist_from_bin((const char *)data, size, &plist);

    // Call the function-under-test
    const char *data_ptr = plist_get_data_ptr(plist, &length);

    // Ensure the plist is freed after use
    if (plist != NULL) {
        plist_free(plist);
    }

    return 0;
}