extern "C" {
#include <stdint.h>
#include <stdlib.h>
#include "/src/libplist/libcnary/include/node.h"
#include "/src/libplist/include/plist/plist.h"
}

extern "C" int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    // Initialize variables
    plist_t plist = NULL;
    int32_t date1 = 0;
    int32_t date2 = 0;

    // Ensure there is enough data to read two int32_t values
    if (size >= sizeof(int32_t) * 2) {
        // Assign values from the data to date1 and date2
        date1 = *(reinterpret_cast<const int32_t*>(data));
        date2 = *(reinterpret_cast<const int32_t*>(data + sizeof(int32_t)));

        // Create a plist node to use with plist_date_val_compare
        plist = plist_new_date(date1, 0); // Create a dummy plist date node
    }

    if (plist != NULL) {
        // Call the function-under-test
        int result = plist_date_val_compare(plist, date1, date2);

        // Free the plist node
        plist_free(plist);
    }

    // Return 0 as required by the LLVMFuzzerTestOneInput function signature
    return 0;
}