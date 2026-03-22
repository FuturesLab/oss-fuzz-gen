#include <stdint.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create at least two plist objects
    if (size < 2) {
        return 0;
    }

    // Create a plist array
    plist_t array = plist_new_array();

    // Create a plist item from the first byte of data
    plist_t item = plist_new_data((const char *)data, 1);

    // Use the second byte of data as the index (cast to uint32_t)
    uint32_t index = static_cast<uint32_t>(data[1]);

    // Call the function-under-test
    plist_array_insert_item(array, item, index);

    // Free the plist objects
    plist_free(array);
    plist_free(item);

    return 0;
}