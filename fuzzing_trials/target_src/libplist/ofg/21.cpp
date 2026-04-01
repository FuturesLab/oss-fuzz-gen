extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating non-empty strings
    if (size < 4) return 0;

    // Initialize plist_t variables
    plist_t source_dict = plist_new_dict();
    plist_t dest_dict = plist_new_dict();

    // Create strings from the input data
    char key1[3] = {0};
    char key2[3] = {0};

    key1[0] = data[0];
    key1[1] = data[1];
    key2[0] = data[2];
    key2[1] = data[3];

    // Add some integer values to the source dictionary
    plist_dict_set_item(source_dict, key1, plist_new_uint(42));
    plist_dict_set_item(source_dict, key2, plist_new_uint(84));

    // Call the function-under-test
    plist_err_t result = plist_dict_copy_int(source_dict, dest_dict, key1, key2);

    // Clean up
    plist_free(source_dict);
    plist_free(dest_dict);

    return 0;
}