#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_175(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Create a plist object from the input data
    plist_t plist = plist_new_data((const char *)data, size);
    if (!plist) {
        return 0;
    }

    // Initialize a uint64_t variable to store the UID value
    uint64_t uid_val = 0;

    // Call the function-under-test
    plist_get_uid_val(plist, &uid_val);

    // Clean up
    plist_free(plist);

    return 0;
}