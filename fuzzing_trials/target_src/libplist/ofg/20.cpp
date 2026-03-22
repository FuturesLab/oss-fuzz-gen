#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract necessary parameters
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Initialize plist_t variables
    plist_t array = plist_new_array();
    plist_t item = plist_new_string("test_item");

    // Extract a uint32_t index from the input data
    uint32_t index = *((uint32_t *)data);

    // Call the function-under-test
    plist_array_set_item(array, item, index);

    // Clean up
    plist_free(array);
    plist_free(item);

    return 0;
}