extern "C" {
#include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    plist_t plist = NULL;
    plist_t item = NULL;

    // Create a new plist array
    plist = plist_new_array();

    // Add an item to the plist array if size is greater than zero
    if (size > 0) {
        item = plist_new_data((const char*)data, size);
        plist_array_append_item(plist, item);
    }

    // Call the function-under-test
    plist_array_item_remove(plist);

    // Free the plist
    plist_free(plist);

    return 0;
}