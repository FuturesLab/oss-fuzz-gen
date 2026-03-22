#include <stdint.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    if (size < sizeof(uint64_t)) {
        return 0; // Ensure there's enough data to construct a uint64_t
    }

    // Convert the first 8 bytes of data to a uint64_t value
    uint64_t uid_value = 0;
    for (size_t i = 0; i < sizeof(uint64_t); ++i) {
        uid_value |= ((uint64_t)data[i] << (i * 8));
    }

    // Call the function-under-test
    plist_t plist = plist_new_uid(uid_value);

    // Clean up the plist object if it was created
    if (plist != NULL) {
        plist_free(plist);
    }

    return 0;
}