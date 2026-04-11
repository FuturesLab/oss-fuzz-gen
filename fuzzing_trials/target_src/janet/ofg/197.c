#include <stdint.h>
#include <stdlib.h>
#include <string.h> // For memcpy
#include <janet.h>  // Ensure this includes JanetFuncDef and janet_disasm

int LLVMFuzzerTestOneInput_197(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for a JanetFuncDef structure
    if (size < sizeof(JanetFuncDef)) {
        return 0;
    }

    // Allocate memory for a JanetFuncDef structure
    JanetFuncDef *funcDef = (JanetFuncDef *)malloc(sizeof(JanetFuncDef));
    if (!funcDef) {
        return 0;
    }

    // Initialize the JanetFuncDef structure with zeroes
    // This helps avoid undefined behavior due to uninitialized fields
    memset(funcDef, 0, sizeof(JanetFuncDef));

    // Copy data into the JanetFuncDef structure
    memcpy(funcDef, data, sizeof(JanetFuncDef));

    // Initialize the Janet runtime
    janet_init();

    // Validate the bytecode and length before calling janet_disasm
    if (funcDef->bytecode && funcDef->bytecode_length > 0) {
        // Ensure bytecode points to valid memory within the input data
        if ((size_t)(funcDef->bytecode) + funcDef->bytecode_length <= size) {
            // Call the function-under-test
            Janet result = janet_disasm(funcDef);
            (void)result; // Suppress unused variable warning
        }
    }

    // Clean up Janet runtime
    janet_deinit();

    // Free allocated memory
    free(funcDef);

    return 0;
}