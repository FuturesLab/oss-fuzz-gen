extern "C" {
    #include <plist/plist.h>
}

#include <cstring> // Include the necessary C++ library for memcpy

extern "C" int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a plist and an int64_t value
    if (size < sizeof(int64_t)) {
        return 0;
    }

    // Create a plist node with an integer value
    plist_t plist_node = plist_new_int((int64_t)data[0]);

    // Extract an int64_t value from the input data
    int64_t int_value;
    memcpy(&int_value, data, sizeof(int64_t));

    // Call the function-under-test
    int result = plist_int_val_compare(plist_node, int_value);

    // Clean up the plist node
    plist_free(plist_node);

    return 0;
}