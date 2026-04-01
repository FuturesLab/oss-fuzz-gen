#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "plist/plist.h"

    int plist_data_val_compare(plist_t, const uint8_t *, size_t);
}

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Ensure size is non-zero for the second parameter
    if (size == 0) return 0;

    // Create a plist object
    plist_t plist = plist_new_data(reinterpret_cast<const char*>(data), size);
    if (!plist) return 0;

    // Call the function-under-test
    int result = plist_data_val_compare(plist, data, size);

    // Free the plist object
    plist_free(plist);

    return 0;
}