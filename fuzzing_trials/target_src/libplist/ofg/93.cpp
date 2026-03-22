extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Not enough data to extract a uint32_t index
    }

    // Create a plist array
    plist_t plist = plist_new_array();

    // Add some dummy items to the plist array to ensure it's not empty
    for (uint32_t i = 0; i < 10; ++i) {
        plist_t item = plist_new_uint(i);
        plist_array_append_item(plist, item);
    }

    // Extract a uint32_t index from the input data
    uint32_t index = *(reinterpret_cast<const uint32_t*>(data));

    // Call the function-under-test
    plist_array_remove_item(plist, index);

    // Clean up
    plist_free(plist);

    return 0;
}