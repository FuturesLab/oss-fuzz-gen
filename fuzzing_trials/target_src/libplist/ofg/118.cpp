#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int plist_uid_val_compare(plist_t node, uint64_t uid);

extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Initialize a plist node
    plist_t node = plist_new_uid(0); // Create a new UID node with initial value 0

    // Ensure that the data size is sufficient to create a meaningful UID
    if (size >= sizeof(uint64_t)) {
        // Extract a uint64_t value from the input data
        uint64_t uid = 0;
        for (size_t i = 0; i < sizeof(uint64_t); ++i) {
            uid |= ((uint64_t)data[i]) << (i * 8);
        }

        // Set the UID value in the plist node
        plist_set_uid_val(node, uid);

        // Call the function-under-test
        int result = plist_uid_val_compare(node, uid);

        // Optionally use the result to avoid compiler warnings
        (void)result;
    }

    // Free the plist node
    plist_free(node);

    return 0;
}