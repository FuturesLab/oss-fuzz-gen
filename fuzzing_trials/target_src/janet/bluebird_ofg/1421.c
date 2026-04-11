#include <stdint.h>
#include <stddef.h>
#include "janet.h"

// Function-under-test
Janet janet_asm_decode_instruction(uint32_t);

// Helper function to initialize Janet runtime
void initialize_janet_1421() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

int LLVMFuzzerTestOneInput_1421(const uint8_t *data, size_t size) {
    // Ensure size is at least 4 bytes to read a uint32_t
    if (size < 4) {
        return 0;
    }

    // Initialize Janet runtime
    initialize_janet_1421();

    // Read the first 4 bytes from the data to form a uint32_t
    uint32_t instruction = *(const uint32_t *)data;

    // Call the function-under-test
    Janet result = janet_asm_decode_instruction(instruction);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    // Clean up Janet runtime if necessary
    // Note: In a real fuzzing environment, you might want to avoid cleaning up
    // and just initialize once, but this depends on the specific requirements
    // and behavior of the Janet library.

    return 0;
}