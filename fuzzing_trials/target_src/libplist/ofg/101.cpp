extern "C" {
    #include <stdint.h>
    #include <stdlib.h>
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to be used
    if (size < 1) {
        return 0;
    }

    // Create a plist node of type boolean
    plist_t node = plist_new_bool(data[0] % 2); // Use the first byte to set the boolean value

    // Prepare a uint8_t variable to hold the boolean value
    uint8_t bool_val = 0;

    // Call the function-under-test
    plist_get_bool_val(node, &bool_val);

    // Clean up the plist node
    plist_free(node);

    return 0;
}