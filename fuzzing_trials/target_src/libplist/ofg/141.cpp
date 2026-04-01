#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    // Initialize plist_t variable
    plist_t plist = plist_new_dict();

    // Initialize int32_t variables
    int32_t sec = 0;
    int32_t usec = 0;

    // Ensure that the size is sufficient to create a valid plist node
    if (size > 0) {
        // Create a plist node from the input data
        plist_t node = plist_new_data((const char*)data, (uint32_t)size);
        plist_dict_set_item(plist, "test_data", node);

        // Attempt to convert the data into a date type to increase coverage
        plist_t date_node = plist_new_date(sec, usec);
        plist_dict_set_item(plist, "test_date", date_node);

        // Call the function-under-test
        plist_get_date_val(date_node, &sec, &usec);
    }

    // Clean up
    plist_free(plist);

    return 0;
}