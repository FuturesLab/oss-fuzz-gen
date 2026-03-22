#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Initialize plist_t and uint64_t* variables
    plist_t plist = NULL;
    uint64_t length = 0;

    // Create a plist from the input data
    if (size > 0) {
        plist_from_bin((const char *)data, size, &plist);
    }

    // Call the function-under-test
    const char *result = plist_get_string_ptr(plist, &length);

    // Output the result for debugging purposes
    if (result != NULL) {
        printf("String: %s, Length: %llu\n", result, (unsigned long long)length);
    }

    // Free the plist
    if (plist != NULL) {
        plist_free(plist);
    }

    return 0;
}