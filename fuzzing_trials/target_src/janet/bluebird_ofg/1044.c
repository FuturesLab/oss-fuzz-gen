#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"  // Assuming the header file for Janet is named janet.h

extern Janet janet_asm_decode_instruction(uint32_t);

int LLVMFuzzerTestOneInput_1044(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0;  // Not enough data to form a uint32_t
    }

    // Use memcpy to safely extract a uint32_t from the input data
    uint32_t instruction;
    memcpy(&instruction, data, sizeof(uint32_t));

    // Ensure the Janet environment is initialized before calling janet_asm_decode_instruction
    janet_init();

    // Call the function-under-test
    Janet result = janet_asm_decode_instruction(instruction);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    // Clean up the Janet environment after the function call
    janet_deinit();

    return 0;
}