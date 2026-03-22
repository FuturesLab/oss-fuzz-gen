#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int plist_uid_val_compare(plist_t plist, uint64_t uid);

extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    plist_t plist = NULL;
    uint64_t uid = 0;

    // Ensure the size is large enough to create a plist and a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Create a plist node from the input data
    plist_from_bin((const char*)data, size, &plist);

    // Extract a uint64_t value from the data
    uid = *((uint64_t*)data);

    // Call the function-under-test
    plist_uid_val_compare(plist, uid);

    // Free the plist to avoid memory leaks
    if (plist != NULL) {
        plist_free(plist);
    }

    return 0;
}