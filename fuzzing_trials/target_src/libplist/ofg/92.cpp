#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for the test
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Initialize the plist
    plist_t plist = plist_new_array();

    // Add some dummy data to the plist array to ensure there are items to remove
    for (uint32_t i = 0; i < 10; ++i) {
        plist_t item = plist_new_uint(i);
        plist_array_append_item(plist, item);
    }

    // Extract an index from the input data
    uint32_t index = *(reinterpret_cast<const uint32_t*>(data));

    // Call the function-under-test
    plist_array_remove_item(plist, index);

    // Clean up
    plist_free(plist);

    return 0;
}