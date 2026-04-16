#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Function-under-test
void *janet_nanbox_to_pointer(Janet);

// Fuzzing harness
int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create a Janet value
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Create a Janet value from the input data
    Janet janet_value;
    memcpy(&janet_value, data, sizeof(Janet));

    // Call the function-under-test
    void *result = janet_nanbox_to_pointer(janet_value);

    // Use result in some way to prevent compiler optimizations from removing the call
    if (result) {
        // Do something with the result, like printing or logging
    }

    return 0;
}