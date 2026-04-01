#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    #include "/src/libplist/libcnary/include/node.h"
    #include "/src/libplist/include/plist/plist.h"

    void plist_get_real_val(plist_t plist, double *value);
}

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    plist_t plist;
    double value = 0.0;

    // Create a plist object from the input data
    if (size > 0) {
        plist = plist_new_data((const char *)data, size);
    } else {
        plist = plist_new_data("default", 7);  // Fallback to a default value if size is 0
    }

    // Call the function-under-test
    plist_get_real_val(plist, &value);

    // Clean up
    plist_free(plist);

    return 0;
}