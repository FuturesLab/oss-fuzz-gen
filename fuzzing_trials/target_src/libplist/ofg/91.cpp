#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for creating a string
    if (size < 1) {
        return 0;
    }

    // Create a plist node of type string
    plist_t plist_node = plist_new_string("fuzz_string");

    // Copy the data into a null-terminated string
    char *input_string = (char *)malloc(size + 1);
    if (input_string == NULL) {
        plist_free(plist_node);
        return 0;
    }
    memcpy(input_string, data, size);
    input_string[size] = '\0';

    // Call the function-under-test
    int result = plist_string_val_compare(plist_node, input_string);

    // Clean up
    free(input_string);
    plist_free(plist_node);

    return 0;
}