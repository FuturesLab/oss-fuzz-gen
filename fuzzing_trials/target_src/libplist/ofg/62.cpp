extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read a boolean value
    if (size < 1) {
        return 0;
    }

    // Initialize a plist object
    plist_t plist = plist_new_bool(0); // Initialize with a default boolean value

    // Extract a boolean value from the input data
    uint8_t bool_val = data[0] % 2; // Ensure it's either 0 or 1

    // Call the function-under-test
    plist_set_bool_val(plist, bool_val);

    // Clean up
    plist_free(plist);

    return 0;
}