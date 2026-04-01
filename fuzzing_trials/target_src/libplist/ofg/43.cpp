extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract two int32_t values
    if (size < sizeof(int32_t) * 2) {
        return 0;
    }

    // Initialize plist
    plist_t plist = plist_new_dict();

    // Extract two int32_t values from the data
    int32_t val1 = *(reinterpret_cast<const int32_t*>(data));
    int32_t val2 = *(reinterpret_cast<const int32_t*>(data + sizeof(int32_t)));

    // Call the function-under-test
    plist_set_date_val(plist, val1, val2);

    // Clean up
    plist_free(plist);

    return 0;
}