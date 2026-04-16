#include <janet.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Initialize Janet VM
    janet_init();

    // Declare and initialize parameters for janet_compile_lint
    Janet source;
    JanetTable *env = janet_table(10); // Create a table with initial capacity
    JanetArray *output = janet_array(10); // Create an array with initial capacity

    // Ensure the data is not NULL and has a size greater than zero
    if (size > 0) {
        // Use the input data as a string to create a Janet string
        source = janet_stringv(data, size);

        // Call the function-under-test
        JanetCompileResult result = janet_compile_lint(source, env, data, output);

        // Optional: Use the result in some way or perform additional checks
        (void)result; // Suppress unused variable warning
    }

    // Cleanup Janet VM
    janet_deinit();

    return 0;
}