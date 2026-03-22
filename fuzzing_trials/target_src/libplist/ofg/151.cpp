extern "C" {
#include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // Declare and initialize plist variables
    plist_t array = plist_new_array();
    plist_t item = plist_new_string("test_item");

    // Ensure the size is non-zero to avoid division by zero
    if (size == 0) return 0;

    // Use the first byte of data to determine the index
    uint32_t index = static_cast<uint32_t>(data[0] % (size + 1));

    // Call the function-under-test
    plist_array_insert_item(array, item, index);

    // Clean up and free allocated memory
    plist_free(array);
    plist_free(item);

    return 0;
}