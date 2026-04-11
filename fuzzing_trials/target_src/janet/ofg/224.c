#include <stddef.h>
#include <stdint.h>

// Assume the function is declared in some header file
void janet_clear_memory();

int LLVMFuzzerTestOneInput_224(const uint8_t *data, size_t size) {
    // The function janet_clear_memory does not take any parameters
    // and does not return any value. We can call it directly.
    janet_clear_memory();

    return 0;
}