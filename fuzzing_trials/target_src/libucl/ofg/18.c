#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract a ucl_type_t value
    if (size < sizeof(ucl_type_t)) {
        return 0;
    }

    // Extract a ucl_type_t value from the input data
    ucl_type_t type = *(ucl_type_t *)data;

    // Call the function-under-test
    const char *type_str = ucl_object_type_to_string(type);

    // Use the result to avoid compiler optimizations that might skip the call
    if (type_str != NULL) {
        // Do something trivial with the result, like checking its length
        volatile size_t len = 0;
        while (type_str[len] != '\0') {
            len++;
        }
    }

    return 0;
}