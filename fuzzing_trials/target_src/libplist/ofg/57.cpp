#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" {
    plist_t plist_new_data(const char *val, uint64_t length);
    void plist_free(plist_t plist);
    int plist_data_val_contains(plist_t plist, const uint8_t *data, size_t size);
}

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for testing
    if (size < 1) {
        return 0;
    }

    // Create a plist object
    plist_t plist = plist_new_data(reinterpret_cast<const char*>(data), size);
    if (!plist) {
        return 0;
    }

    // Call the function-under-test
    int result = plist_data_val_contains(plist, data, size);

    // Clean up
    plist_free(plist);

    return 0;
}