#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_166(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a plist
    if (size == 0) {
        return 0;
    }

    // Create a plist node from the input data
    plist_t plist = plist_new_data((const char*)data, (uint32_t)size);

    // Call the function-under-test
    plist_free(plist);

    return 0;
}