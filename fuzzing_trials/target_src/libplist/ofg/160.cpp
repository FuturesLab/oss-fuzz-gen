#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" {
    // Function-under-test
    char plist_compare_node_value(plist_t node1, plist_t node2);
}

extern "C" int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Not enough data to create valid plist nodes
    }

    // Ensure null-terminated strings for plist_new_string
    size_t len1 = data[0] % (size - 1) + 1; // Ensure at least 1 byte for the first string
    size_t len2 = data[1] % (size - len1 - 1) + 1; // Ensure at least 1 byte for the second string

    char *str1 = (char *)malloc(len1 + 1);
    char *str2 = (char *)malloc(len2 + 1);

    if (!str1 || !str2) {
        free(str1);
        free(str2);
        return 0; // Memory allocation failed
    }

    memcpy(str1, data + 2, len1);
    memcpy(str2, data + 2 + len1, len2);

    str1[len1] = '\0';
    str2[len2] = '\0';

    // Initialize plist nodes
    plist_t node1 = plist_new_string(str1);
    plist_t node2 = plist_new_string(str2);

    // Call the function-under-test
    plist_compare_node_value(node1, node2);

    // Clean up plist nodes and allocated strings
    plist_free(node1);
    plist_free(node2);
    free(str1);
    free(str2);

    return 0;
}