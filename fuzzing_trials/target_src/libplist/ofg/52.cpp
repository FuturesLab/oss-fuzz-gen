#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include the string.h library for strlen function
#include <plist/plist.h>

extern "C" {
    int plist_data_val_compare_with_size(plist_t, const uint8_t *, size_t);
}

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a plist
    if (size < 1) {
        return 0;
    }

    // Create a plist node of type PLIST_DATA
    plist_t node = plist_new_data((const char *)data, size);

    // Check if the node was created successfully
    if (!node) {
        return 0;
    }

    // Create a second plist node to compare with
    // Instead of creating a node with the same data, create a node with different data
    const char *other_data = "other_data";
    size_t other_size = strlen(other_data);
    plist_t node_to_compare = plist_new_data(other_data, other_size);

    // Check if the second node was created successfully
    if (!node_to_compare) {
        plist_free(node);
        return 0;
    }

    // Call the function-under-test
    int result = plist_data_val_compare_with_size(node, (const uint8_t *)other_data, other_size);

    // Free the plist nodes
    plist_free(node);
    plist_free(node_to_compare);

    // Return the result to ensure the function is utilized
    return result;
}