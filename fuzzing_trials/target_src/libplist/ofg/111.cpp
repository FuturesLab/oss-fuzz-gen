#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    uint64_t uid = 0;

    // Ensure there's enough data to read a uint64_t
    if (size >= sizeof(uint64_t)) {
        // Copy the first 8 bytes from data into uid
        uid = *((uint64_t*)data);
    }

    // Call the function-under-test
    plist_t result = plist_new_uid(uid);

    // Clean up the plist object if necessary
    if (result != NULL) {
        plist_free(result);
    }

    return 0;
}