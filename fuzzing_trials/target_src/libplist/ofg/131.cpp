extern "C" {
    #include <stdint.h>
    #include <stdlib.h>
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Extract a uint64_t value from the input data
    uint64_t uid_val = 0;
    for (size_t i = 0; i < sizeof(uint64_t); ++i) {
        uid_val = (uid_val << 8) | data[i];
    }

    // Create a new plist node with the extracted uid_val
    plist_t node = plist_new_uid(uid_val);

    // Call the function-under-test
    plist_set_uid_val(node, uid_val);

    // Clean up the plist node
    plist_free(node);

    return 0;
}