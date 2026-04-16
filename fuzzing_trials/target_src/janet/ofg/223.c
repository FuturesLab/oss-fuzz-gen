#include <stdint.h>
#include <stddef.h> // Include this header to define 'size_t'

// Assuming the function janet_clear_memory is defined somewhere
void janet_clear_memory();

int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
    // Call the function-under-test
    janet_clear_memory();

    return 0;
}