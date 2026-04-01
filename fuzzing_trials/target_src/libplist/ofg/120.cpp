#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include the necessary header for memcpy

extern "C" {
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Ensure that we have enough data to create a plist and a double value
    if (size < sizeof(double)) {
        return 0;
    }

    // Interpret the first sizeof(double) bytes of data as a double
    double input_value;
    memcpy(&input_value, data, sizeof(double));

    // Create a plist node from the input data
    plist_t node = plist_new_real(input_value);

    // Initialize a double to store the value
    double real_val = 0.0;

    // Call the function-under-test
    plist_get_real_val(node, &real_val);

    // Perform a basic check to ensure the function is working as expected
    if (real_val != input_value) {
        abort(); // This will help identify discrepancies during fuzzing
    }

    // Clean up the plist node
    plist_free(node);

    return 0;
}