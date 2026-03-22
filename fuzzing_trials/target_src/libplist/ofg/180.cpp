#include <stdint.h>
#include <stddef.h>
#include <plist/plist.h>
#include <string.h>
#include <stdlib.h>

extern "C" int plist_string_val_compare_with_size(plist_t node, const char *val, size_t len);

extern "C" int LLVMFuzzerTestOneInput_180(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Create a plist node with a string value
    plist_t node = plist_new_string("test");

    // Use part of the input data as the string to compare
    size_t str_len = size - 1;
    char *str_val = (char *)malloc(str_len + 1);
    if (!str_val) {
        plist_free(node);
        return 0;
    }
    memcpy(str_val, data, str_len);
    str_val[str_len] = '\0'; // Null-terminate the string

    // Call the function-under-test
    int result = plist_string_val_compare_with_size(node, str_val, str_len);

    // Clean up
    free(str_val);
    plist_free(node);

    return 0;
}