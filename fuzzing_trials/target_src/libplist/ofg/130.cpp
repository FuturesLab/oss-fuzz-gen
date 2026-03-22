#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    plist_t plist = NULL;
    uint64_t uid_val;

    // Ensure that size is large enough to extract a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Initialize plist
    plist = plist_new_uid(0); // Create a new UID plist node with a default value

    // Extract a uint64_t value from the input data
    uid_val = *((uint64_t*)data);

    // Call the function-under-test
    plist_set_uid_val(plist, uid_val);

    // Clean up
    plist_free(plist);

    return 0;
}