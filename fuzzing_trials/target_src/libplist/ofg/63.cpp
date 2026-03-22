extern "C" {
    #include <plist/plist.h>
    #include <string.h> // Include the string.h library for memcpy
}

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    // Initialize plist_t object
    plist_t plist = plist_new_dict();

    // Ensure size is large enough to extract a uint64_t value
    if (size < sizeof(uint64_t)) {
        plist_free(plist);
        return 0;
    }

    // Extract a uint64_t value from the input data
    uint64_t uint_val;
    memcpy(&uint_val, data, sizeof(uint64_t));

    // Call the function-under-test
    plist_set_uint_val(plist, uint_val);

    // Clean up
    plist_free(plist);

    return 0;
}