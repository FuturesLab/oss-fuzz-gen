#include <stdint.h>
#include <stddef.h>  // Include this header to define size_t

// Assume that the janet_sweep function is defined in an external library
extern void janet_sweep();

int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
    // The janet_sweep function does not take any parameters, so we can call it directly.
    janet_sweep();

    return 0;
}