#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Interpret the input data as a Janet value
    Janet janet_value;
    memcpy(&janet_value, data, sizeof(Janet));

    // Call the function-under-test
    void *result = janet_nanbox_to_pointer(janet_value);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result != NULL) {
        // Do something trivial with the result, e.g., print the address
        printf("Pointer address: %p\n", result);
    }

    return 0;
}