#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    // Initialize a plist object
    plist_t plist = plist_new_array();

    // Add some items to the plist array to ensure it's not empty
    plist_array_append_item(plist, plist_new_string("item1"));
    plist_array_append_item(plist, plist_new_string("item2"));
    plist_array_append_item(plist, plist_new_string("item3"));

    // Ensure the index is within bounds of the plist array
    uint32_t index = size % 3; // Since we added 3 items, use modulo 3

    // Call the function-under-test
    plist_t item = plist_array_get_item(plist, index);

    // Clean up
    plist_free(item);
    plist_free(plist);

    return 0;
}