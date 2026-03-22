extern "C" {
    #include <stdint.h>
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    if (size < sizeof(uint64_t)) {
        return 0; // Not enough data to form a uint64_t
    }

    // Extract a uint64_t from the input data
    uint64_t value = 0;
    for (size_t i = 0; i < sizeof(uint64_t); ++i) {
        value |= ((uint64_t)data[i]) << (i * 8);
    }

    // Call the function-under-test
    plist_t plist = plist_new_uint(value);

    // Free the created plist to avoid memory leaks
    plist_free(plist);

    return 0;
}