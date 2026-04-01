#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a plist object.
    if (size < 8) { // Minimum size needed to create a valid date plist
        return 0;
    }

    // Create a plist object from the input data
    plist_t plist = plist_new_data((const char*)data, size);
    if (!plist) {
        return 0;
    }

    // Attempt to interpret the data as a date
    plist_t date_plist = plist_new_date(data[0], data[1]); // Using first two bytes as sec and usec
    if (!date_plist) {
        plist_free(plist);
        return 0;
    }

    // Initialize the int32_t variables
    int32_t sec = 0;
    int32_t usec = 0;

    // Call the function-under-test
    plist_get_date_val(date_plist, &sec, &usec);

    // Clean up
    plist_free(date_plist);
    plist_free(plist);

    return 0;
}