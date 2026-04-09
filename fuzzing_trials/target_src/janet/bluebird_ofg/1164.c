#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "janet.h"

// Initialize Janet runtime
void initialize_janet_1164() {
    janet_init();
}

// Clean up Janet runtime
void cleanup_janet() {
    janet_deinit();
}

extern JanetSymbol janet_symbol_gen();

int LLVMFuzzerTestOneInput_1164(const uint8_t *data, size_t size) {
    (void)data;  // Unused parameter
    (void)size;  // Unused parameter

    // Initialize Janet runtime before using any Janet functions
    initialize_janet_1164();

    // Call the function-under-test
    JanetSymbol symbol = janet_symbol_gen();

    // Use the generated symbol in some way to avoid compiler optimizations
    // that might remove the call to janet_symbol_gen.
    // Here we simply print the symbol value.
    printf("Generated JanetSymbol: %d\n", symbol);

    // Clean up Janet runtime after use
    cleanup_janet();

    return 0;
}