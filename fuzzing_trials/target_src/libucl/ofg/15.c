#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract a ucl_type_t value
    if (size < sizeof(ucl_type_t)) {
        return 0;
    }

    // Extract a ucl_type_t value from the input data
    ucl_type_t type = *(ucl_type_t *)data;

    // Call the function-under-test
    const char *type_str = ucl_object_type_to_string(type);

    // Optionally, do something with the result to prevent compiler optimizations
    if (type_str != NULL) {
        // For example, just check the first character
        volatile char first_char = type_str[0];
        (void)first_char;  // Suppress unused variable warning
    }

    return 0;
}