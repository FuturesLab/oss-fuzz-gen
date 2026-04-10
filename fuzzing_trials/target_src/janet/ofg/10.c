#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Initialize Janet environment
    janet_init();

    // Create a JanetBuffer
    JanetBuffer *buffer = janet_buffer(10);

    // Create a Janet value
    Janet janet_value = janet_wrap_number(42);

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Set an integer option
    int options = 0;

    // Call the function-under-test
    janet_marshal(buffer, janet_value, table, options);

    // Clean up Janet environment
    janet_deinit();

    return 0;
}