extern "C" {
    #include <stdint.h>
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Ensure there is at least one byte of data to use for the boolean value
    if (size < 1) {
        return 0;
    }

    // Create a plist node of type boolean
    plist_t node = plist_new_bool(0); // Initialize with a default value

    // Use the first byte of the input data as the boolean value
    uint8_t bool_value = data[0] % 2; // Ensure it's either 0 or 1

    // Call the function-under-test
    plist_set_bool_val(node, bool_value);

    // Additional code to utilize the node and increase code coverage
    uint8_t retrieved_value;
    plist_get_bool_val(node, &retrieved_value);

    // Check if the set value and retrieved value are the same
    if (retrieved_value != bool_value) {
        // Handle the discrepancy if needed
    }

    // Free the plist node
    plist_free(node);

    return 0;
}