extern "C" {
    #include "/src/libplist/libcnary/include/node.h"
    #include "/src/libplist/include/plist/plist.h"
}

extern "C" int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    int debug_level = 0;

    // Ensure size is not zero to avoid accessing data[0] when size is zero
    if (size > 0) {
        // Use the first byte of data to set the debug level
        debug_level = static_cast<int>(data[0]);
    }

    // Call the function-under-test with the debug level
    plist_set_debug(debug_level);

    return 0;
}