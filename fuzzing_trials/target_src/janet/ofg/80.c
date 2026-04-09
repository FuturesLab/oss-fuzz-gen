#include <stdint.h>
#include <stddef.h>
#include <janet.h>

extern JanetFunction * janet_optfunction(const Janet *argv, int32_t argc, int32_t n, JanetFunction *def);

int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet) + sizeof(int32_t) * 2 + sizeof(JanetFunction *)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Prepare arguments for janet_optfunction
    const Janet *argv = (const Janet *)data;
    int32_t argc = (int32_t)(size / sizeof(Janet));
    int32_t n = argc > 0 ? 1 : 0; // Ensure n is a valid index
    JanetFunction *def = (JanetFunction *)(argv + argc - 1); // Use last element as default

    // Call the function-under-test
    JanetFunction *result = janet_optfunction(argv, argc, n, def);

    // Clean up Janet VM
    janet_deinit();

    return 0;
}