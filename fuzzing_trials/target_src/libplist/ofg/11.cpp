extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a plist node
    if (size < 1) {
        return 0;
    }

    // Create a plist array
    plist_t plist_array = plist_new_array();

    // Add multiple dummy items to the plist array
    plist_t item1 = plist_new_string("item1");
    plist_t item2 = plist_new_string("item2");
    plist_t item3 = plist_new_string("item3");
    plist_array_append_item(plist_array, item1);
    plist_array_append_item(plist_array, item2);
    plist_array_append_item(plist_array, item3);

    // Use the fuzz input to determine which item to remove
    size_t index_to_remove = data[0] % 3; // Choose an index based on fuzz input
    plist_t item_to_remove = plist_array_get_item(plist_array, index_to_remove);
    plist_array_item_remove(item_to_remove);

    // Cleanup
    plist_free(plist_array);

    return 0;
}