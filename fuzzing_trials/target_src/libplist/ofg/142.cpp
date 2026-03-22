extern "C" {
    #include <stdint.h>
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    // Initialize plist_t
    plist_t plist = plist_new_dict();

    // Ensure plist is not NULL and has some data
    if (size > 0) {
        plist_dict_set_item(plist, "key", plist_new_data((const char*)data, size));
    } else {
        plist_dict_set_item(plist, "key", plist_new_uint(42)); // Default non-null value
    }

    // Call the function-under-test
    uint64_t value = 0;
    plist_t node = plist_dict_get_item(plist, "key");
    if (node) {
        plist_get_uint_val(node, &value);
    }

    // Clean up
    plist_free(plist);

    return 0;
}