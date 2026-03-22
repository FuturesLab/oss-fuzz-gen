extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    // Create a plist object from the input data
    plist_t plist = NULL;
    plist_from_bin((const char*)data, size, &plist);

    // Call the function-under-test
    uint32_t dict_size = plist_dict_get_size(plist);

    // Clean up the plist object
    plist_free(plist);

    return 0;
}