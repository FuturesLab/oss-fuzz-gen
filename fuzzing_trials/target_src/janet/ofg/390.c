#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// A simple example of a JanetCFunction
static Janet my_cfunction(int32_t argc, Janet *argv) {
    // This function does nothing, just returns nil
    (void)argc; // Suppress unused variable warning
    (void)argv; // Suppress unused variable warning
    return janet_wrap_nil();
}

int LLVMFuzzerTestOneInput_390(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for our needs
    if (size < sizeof(JanetCFunction)) {
        return 0;
    }

    // Initialize the Janet runtime
    janet_init();

    // Use the provided data to create a JanetCFunction pointer
    JanetCFunction cfunc = my_cfunction;

    // Wrap the C function in a Janet object
    Janet wrapped_function = janet_wrap_cfunction(cfunc);

    // Clean up the Janet runtime
    janet_deinit();

    return 0;
}