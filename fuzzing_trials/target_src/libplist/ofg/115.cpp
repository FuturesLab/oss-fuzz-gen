extern "C" {
    #include <stdint.h>
    #include <stdlib.h>
    #include <plist/plist.h>

    int plist_uint_val_compare(plist_t plist, uint64_t value);
}

extern "C" int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating a plist and a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Create a plist node
    plist_t plist = plist_new_uint(*(uint64_t*)data);

    // Extract a uint64_t value from the data
    uint64_t value = *(uint64_t*)(data + (size - sizeof(uint64_t)));

    // Call the function-under-test
    int result = plist_uint_val_compare(plist, value);

    // Clean up
    plist_free(plist);

    return 0;
}