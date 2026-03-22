extern "C" {
    #include <plist/plist.h>
}

#include <cstring> // Include the C++ header for memcpy

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    // Check if the size is sufficient for extracting a double value
    if (size < sizeof(double)) {
        return 0;
    }

    // Initialize a plist node
    plist_t node = plist_new_real(0.0);

    // Extract a double value from the input data
    double real_value;
    memcpy(&real_value, data, sizeof(double));

    // Call the function-under-test
    plist_set_real_val(node, real_value);

    // Free the plist node
    plist_free(node);

    return 0;
}